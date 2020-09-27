# Copyright (c) 2017-present, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under the license found in the LICENSE file in
# the root directory of this source tree. An additional grant of patent rights
# can be found in the PATENTS file in the same directory.

from fairseq.optim.lr_scheduler import FairseqLRScheduler, register_lr_scheduler


@register_lr_scheduler('capped_inverse_sqrt')
class CappedInverseSquareRootSchedule(FairseqLRScheduler):
    """Decay the LR based on the inverse square root of the update number.

    We also support a warmup phase where we linearly increase the learning rate
    from some initial learning rate (``--warmup-init-lr``) until the configured
    learning rate (``--lr``). Thereafter we decay proportional to the number of
    updates, with a decay factor set to align with the configured learning rate.

    During warmup::

      lrs = torch.linspace(args.warmup_init_lr, args.lr, args.warmup_updates)
      lr = lrs[update_num]

    After warmup::

      decay_factor = args.lr * sqrt(inv_decay)
      lr = decay_factor / sqrt(update_num)
    """

    def __init__(self, args, optimizer):
        super().__init__(args, optimizer)
        if len(args.lr) > 1:
            raise ValueError(
                'Cannot use a fixed learning rate schedule with inverse_sqrt.'
                ' Consider --lr-scheduler=fixed instead.'
            )
        warmup_end_lr = args.lr[0]
        if args.warmup_init_lr < 0:
            args.warmup_init_lr = warmup_end_lr

        self.inv_decay = args.inv_decay if args.inv_decay > 0 else args.warmup_updates
        # linearly warmup for the first args.warmup_updates
        self.lr_step = (warmup_end_lr - args.warmup_init_lr) / args.warmup_updates

        self.max_lr = warmup_end_lr

        # then, decay prop. to the inverse square root of the update number
        # self.decay_factor = warmup_end_lr * args.warmup_updates**0.5
        self.decay_factor = warmup_end_lr * self.inv_decay ** 0.5

        # initial learning rate
        self.lr = args.warmup_init_lr
        self.optimizer.set_lr(self.lr)

        print(f'inv_decay={self.inv_decay},warmup={args.warmup_updates},decay_factor={self.decay_factor}')

    @staticmethod
    def add_args(parser):
        """Add arguments to the parser for this LR scheduler."""
        # fmt: off
        parser.add_argument('--warmup-updates', default=4000, type=int, metavar='N',
                            help='warmup the learning rate linearly for the first N updates')
        parser.add_argument('--inv-decay', default=-1, type=int, metavar='N',
                            help='inv-decay, set to warmup if not >0')
        parser.add_argument('--warmup-init-lr', default=-1, type=float, metavar='LR',
                            help='initial learning rate during warmup phase; default is args.lr')
        # fmt: on

    def step(self, epoch, val_loss=None):
        """Update the learning rate at the end of the given epoch."""
        super().step(epoch, val_loss)
        # we don't change the learning rate at epoch boundaries
        return self.optimizer.get_lr()

    def step_update(self, num_updates):
        """Update the learning rate after each update."""
        if num_updates < self.args.warmup_updates:
            self.lr = self.args.warmup_init_lr + num_updates*self.lr_step
        else:
            self.lr = min(self.decay_factor * num_updates**-0.5, self.max_lr)
        self.optimizer.set_lr(self.lr)
        return self.lr
