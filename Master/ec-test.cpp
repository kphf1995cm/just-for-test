# include "ec.h"
# include<iostream>
# include<string>
# include<vector>
using namespace std;

// g++ ec-test.cpp -o ect -lerasurecode -ldl

void test_encode_decode(int ds){
    EC ec;
    std::string value(ds,'a');
    std::vector<std::string> encodedData;
    std::vector<std::string> encodedParity;
    uint64_t fragmentLen;
    ec.encode(value,encodedData,encodedParity,fragmentLen);
    std::string restoreValue;
    std::vector<std::string> fragments;
    fragments.push_back(encodedData[0]);
    fragments.push_back(encodedData[1]);
    fragments.push_back(encodedParity[0]);
    fragments.push_back(encodedParity[2]);
    ec.decode(fragments,fragmentLen,restoreValue);
    std::string idxFragment;
    ec.reconstructFragment(fragments,fragmentLen,2,idxFragment);
    cout<<value.compare(restoreValue)<<" ";
    cout<<idxFragment.compare(encodedData[2])<<endl;
}

int main(){
    //EC ec;
    for(int i=200;i<=250;i++){
        //ec.test_encode(i);
        //std::cout<<std::endl;
        test_encode_decode(i);
    }
}

