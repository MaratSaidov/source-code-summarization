// Copyright (c) 2019-present, Facebook, Inc.
// All rights reserved.
//
// This source code is licensed under the license found in the
// LICENSE file in the root directory of this source tree.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <bits/stdc++.h>
using namespace std;
void f_gold ( int arr [ ], int n ) {
  for ( int i = 0;
  i < n;
  i ++ ) {
    arr [ i ] = i + 1;
  }
}


//TOFILL

int main() {
    int n_success = 0;
    vector<vector<int>> param0 {{3,3,6,7,9,11,15,15,17,19,21,23,26,27,37,48,48,51,53,53,59,64,69,69,70,71,72,84,93,96},{66,-28,6,25,-65,19,-86,-86,-90,40,-62},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{85,84,8,36,93,76,14,54,85,86},{-90,-82,-80,-73,-67,-62,-62,-61,-58,-56,-56,-52,-50,-49,-49,-43,-43,-30,-26,-26,-15,-14,-13,-4,10,19,20,22,26,29,34,35,37,45,49,52,54,66,67,80,84,87,89,90},{1,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,0,0,1,1,0,0,0,1,1,0,0,1,0,1,1,1},{10,11,13,19,19,30,33,36,40,42,44,47,49,52,53,58,66,68,72,82,87,89,90,94},{-46,-35,40,-76,-66,-47,36,-82,-43,12,-95,54,58,82,-87,-17,-71,-97,-10,4,23,86,-24},{0,0,0,0,0,1,1,1,1,1,1},{88,76,16,23,40,60,73,32,15,13,5,75,74,52,77,41,53,50,15,7,40,28,32,99,15,85}};
    vector<int> param1 {19,8,26,9,31,29,21,12,6,18};
    vector<vector<int>> filled_function_param0 {{3,3,6,7,9,11,15,15,17,19,21,23,26,27,37,48,48,51,53,53,59,64,69,69,70,71,72,84,93,96},{66,-28,6,25,-65,19,-86,-86,-90,40,-62},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{85,84,8,36,93,76,14,54,85,86},{-90,-82,-80,-73,-67,-62,-62,-61,-58,-56,-56,-52,-50,-49,-49,-43,-43,-30,-26,-26,-15,-14,-13,-4,10,19,20,22,26,29,34,35,37,45,49,52,54,66,67,80,84,87,89,90},{1,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,0,0,1,1,0,0,0,1,1,0,0,1,0,1,1,1},{10,11,13,19,19,30,33,36,40,42,44,47,49,52,53,58,66,68,72,82,87,89,90,94},{-46,-35,40,-76,-66,-47,36,-82,-43,12,-95,54,58,82,-87,-17,-71,-97,-10,4,23,86,-24},{0,0,0,0,0,1,1,1,1,1,1},{88,76,16,23,40,60,73,32,15,13,5,75,74,52,77,41,53,50,15,7,40,28,32,99,15,85}};
    vector<int> filled_function_param1 {19,8,26,9,31,29,21,12,6,18};
    for(int i = 0; i < param0.size(); ++i)
    {
        f_filled(&filled_function_param0[i].front(),filled_function_param1[i]);
        f_gold(&param0[i].front(),param1[i]);
        if(equal(begin(param0[i]), end(param0[i]), begin(filled_function_param0[i])) && param1[i] == filled_function_param1[i])
        {
            n_success+=1;
        }
    }
    cout << "#Results:" << " " << n_success << ", " << param0.size();
    return 0;
}