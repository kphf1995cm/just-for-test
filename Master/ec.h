# ifndef _EC_H_
# define _EC_H_
# include <erasurecode.h>
# include <assert.h>
# include <stdio.h>
# include <iostream>
# include <string>
# include <vector>
// https://github.com/intel/isa-l
// https://opendev.org/openstack/liberasurecode/src/branch/master/doc/api_definition.md
// https://github.com/openstack/liberasurecode/blob/master/include/erasurecode/erasurecode.h

// EC_BACKEND_ISA_L_RS_VAND = 4
// EC_BACKEND_ISA_L_RS_CAUCHY = 7

/*
struct ec_args {
    int k;                  // number of data fragments 
    int m;                  // number of parity fragments 
    int w;                  // word size, in bits (optional) 
    int hd;                 // hamming distance (=m for Reed-Solomon) 

    union {
        struct {
            uint64_t arg1;  // sample arg 
        } null_args;        // args specific to the null codes 
        struct {
            uint64_t x, y;  // reserved for future expansion 
            uint64_t z, a;  // reserved for future expansion 
        } reserved;
    } priv_args1;

    void *priv_args2;       // flexible placeholder for future backend args 
    ec_checksum_type_t ct;  // fragment checksum type 
};
*/

// g++ ec-test.cpp ec.cpp -o ect -lerasurecode -ldl
// https://blog.csdn.net/sean4m/article/details/55211492

// requirement: std=c++11 or std=gnu++11

char *create_buffer(int size, int fill);

class EC{
    private:

        ec_backend_id_t ecbi;
        struct ec_args args;
        int ecDesc;

    public:

        EC(int _k,int _m,int _w,int _hd,ec_backend_id_t _ecbi){
            args = {
                .k = _k,
                .m = _m,
                .w = _w,
                .hd = _hd,
            };
            ecbi=_ecbi;
            init();
        }

        EC(){
            args = {
                .k = 4,
                .m = 4,
                .w = 8,
                .hd = 5,
            };
            ecbi=EC_BACKEND_ISA_L_RS_VAND;
            init();
        }

        ~EC(){
            liberasurecode_instance_destroy(ecDesc);
        }

        void init(){
            ecDesc=liberasurecode_instance_create(ecbi,&args);
        }

        void encode(std::string &value,std::vector<std::string> &encodedData,std::vector<std::string> &encodedParity,uint64_t &fragmentLen);

        void decode(std::vector<std::string> fragments,uint64_t fragmentLen, std::string &oriValue);
        
        void reconstructFragment(std::vector<std::string> fragments,uint64_t fragmentLen,int idx,std::string &idxFragment);
        
        void test_encode(int orig_data_size){
            //printf("orig_data_size:%d\t",orig_data_size);
            struct ec_args isa_l_44_args = {
                .k = 4,
                .m = 4,
                .w = 8,
                .hd = 5,
            };
            int desc=liberasurecode_instance_create(EC_BACKEND_ISA_L_RS_VAND,&isa_l_44_args);

            int rc=0;
            char *orig_data = create_buffer(orig_data_size, 'x');
            char **encoded_data = NULL, **encoded_parity = NULL;
            uint64_t fragment_len = 0;
            //printf("ori_data:%s\n",orig_data);
            
            assert(orig_data != NULL);
            rc=liberasurecode_encode(desc, orig_data, orig_data_size,&encoded_data, &encoded_parity, &fragment_len);
            assert(rc ==0);
            //liberasurecode_encode_cleanup(desc,encoded_data,encoded_parity);
            //printf("encoded_data[2]:%s\n",encoded_data[2]);
            int num_fragments=4;
            char **fragments = (char **)malloc(num_fragments*sizeof(char*));
            fragments[0]=encoded_data[0];
            fragments[1]=encoded_data[1];
            fragments[2]=encoded_parity[0];
            fragments[3]=encoded_parity[1];
            char *out_data=NULL;
            uint64_t out_data_len=0;
            rc=liberasurecode_decode(desc,fragments,num_fragments,fragment_len,0,&out_data,&out_data_len);
            assert(rc==0);
            //printf("out_data:%s\n",out_data);
            if(strcmp(orig_data,out_data)==0){
                //printf("encode/decode success\t");
                printf("%d ",orig_data_size);
            }
            //liberasurecode_decode_cleanup(desc,out_data);

            char *out_fragment=(char *)malloc(fragment_len);
            int destination_idx=2;
            rc=liberasurecode_reconstruct_fragment(desc,fragments,num_fragments,fragment_len,destination_idx,out_fragment);
            assert(rc==0);
            //printf("out_fragment:%s\n",out_fragment);
            //if(strcmp(encoded_data[2],out_fragment)==0){
            //    printf("reconstruct fragment success\t");
            //}

            free(fragments);
            free(out_fragment);
            liberasurecode_encode_cleanup(desc,encoded_data,encoded_parity);
            liberasurecode_decode_cleanup(desc,out_data);
        }
};

# endif