# ifndef _EC_H_
# define _EC_H_
# include <erasurecode.h>
# include <assert.h>
# include <stdio.h>
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

// g++ ec-test.cpp -o ect -lerasurecode -ldl

char *create_buffer(int size, int fill){
    char *buf = (char *)malloc(size);
    memset(buf, fill, size);
    return buf;
}

class EC{
    private:
        int dataNodeNum;
        int codeNodeNum;
        int ecDescriptor;
    public:
        EC(){
        }
        void init(){
            struct ec_args isa_l_44_args = {
                .k = 4,
                .m = 4,
                .w = 8,
                .hd = 5,
            };
            ecDescriptor=liberasurecode_instance_create(EC_BACKEND_ISA_L_RS_VAND,&isa_l_44_args);
            liberasurecode_instance_destroy(ecDescriptor);
        }

        void encode(){

        }
        void decode(){

        }
        void test_encode(){

            struct ec_args isa_l_44_args = {
                .k = 4,
                .m = 4,
                .w = 8,
                .hd = 5,
            };
            int desc=liberasurecode_instance_create(EC_BACKEND_ISA_L_RS_VAND,&isa_l_44_args);

            int rc=0;
            int orig_data_size = 100;
            char *orig_data = create_buffer(orig_data_size, 'x');
            char **encoded_data = NULL, **encoded_parity = NULL;
            uint64_t fragment_len = 0;
            printf("ori_data:%s\n",orig_data);
            
            assert(orig_data != NULL);
            rc=liberasurecode_encode(desc, orig_data, orig_data_size,&encoded_data, &encoded_parity, &fragment_len);
            assert(rc ==0);
            //liberasurecode_encode_cleanup(desc,encoded_data,encoded_parity);
            printf("encoded_data[2]:%s\n",encoded_data[2]);
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
            printf("out_data:%s\n",out_data);
            if(strcmp(orig_data,out_data)==0){
                printf("encode/decode success\n");
            }
            //liberasurecode_decode_cleanup(desc,out_data);

            char *out_fragment=(char *)malloc(fragment_len);
            int destination_idx=2;
            rc=liberasurecode_reconstruct_fragment(desc,fragments,num_fragments,fragment_len,destination_idx,out_fragment);
            assert(rc==0);
            printf("out_fragment:%s\n",out_fragment);
            if(strcmp(encoded_data[2],out_fragment)==0){
                printf("reconstruct fragment success\n");
            }

            free(fragments);
            free(out_fragment);
            liberasurecode_encode_cleanup(desc,encoded_data,encoded_parity);
            liberasurecode_decode_cleanup(desc,out_data);
        }
};

# endif