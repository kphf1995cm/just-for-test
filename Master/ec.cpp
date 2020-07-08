# include "ec.h"

char *create_buffer(int size, int fill){
    char *buf = (char *)malloc(size);
    memset(buf, fill, size);
    return buf;
}

void EC::encode(std::string &value,std::vector<std::string> &encodedData,std::vector<std::string> &encodedParity,uint64_t &fragmentLen){
            int orig_data_size=value.size();
            char *orig_data=new char[value.size()+1];
            strcpy(orig_data,value.c_str());
            char **encoded_data = NULL;
            char **encoded_parity = NULL;

            assert(orig_data != NULL);
            int rc=liberasurecode_encode(ecDesc, orig_data, orig_data_size,&encoded_data, &encoded_parity, &fragmentLen);
            delete []orig_data;
            assert(rc==0);
            int ed_size=args.k;
            int ep_size=args.m;
            for(int i=0;i<ed_size;i++){
                std::string eds(encoded_data[i]);
                encodedData.push_back(eds);
            }
            for(int i=0;i<ep_size;i++){
                std::string eps(encoded_parity[i]);
                encodedParity.push_back(eps);
            }
            liberasurecode_encode_cleanup(ecDesc,encoded_data,encoded_parity);
        }

        void EC::decode(std::vector<std::string> fragments,uint64_t fragmentLen, std::string &oriValue){
            assert(fragments.size()>=args.k);
            char** c_fragments=new char*[fragments.size()];
            for(int i=0;i<fragments.size();i++){
                c_fragments[i]=new char[fragments[i].size()+1];
                strcpy(c_fragments[i],fragments[i].c_str());
            }
            char *out_data=NULL;
            uint64_t out_data_len=0;
            std::cout<<"fragments size: "<<fragments.size()<<" fragmentLen: "<<fragmentLen<<std::endl;
            int rc=liberasurecode_decode(ecDesc,c_fragments,fragments.size(),fragmentLen,0,&out_data,&out_data_len);
            std::cout<<"rc: "<<rc<<std::endl;
            for(int i=0;i<fragments.size();i++){
                delete []c_fragments[i];
            }
            delete []c_fragments;
            std::cout<<"delete success"<<std::endl;
            //assert(rc==0);
            oriValue.assign(out_data);
            std::cout<<"restore oriValue"<<std::endl;
            liberasurecode_decode_cleanup(ecDesc,out_data);
        }

        void EC::reconstructFragment(std::vector<std::string> fragments,uint64_t fragmentLen,int idx,std::string &idxFragment){
            assert(fragments.size()>=args.k);
            char** c_fragments=new char*[fragments.size()];
            for(int i=0;i<fragments.size();i++){
                c_fragments[i]=new char[fragments[i].size()+1];
                strcpy(c_fragments[i],fragments[i].c_str());
            }
            char *out_fragment=new char[fragmentLen];
            int rc=liberasurecode_reconstruct_fragment(ecDesc,c_fragments,fragments.size(),fragmentLen,idx,out_fragment);
            assert(rc!=0);
            for(int i=0;i<fragments.size();i++){
                delete []c_fragments[i];
            }
            delete []c_fragments;
            idxFragment.assign(out_fragment);
            delete []out_fragment;
        }