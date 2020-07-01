# ifndef _KVCLIENT_H_
# define _KVCLIENT_H_

# include<iostream>
# include <grpcpp/grpcpp.h>
# include "kvs.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using kvs::Request;
using kvs::Response;
using kvs::Key;
using kvs::Value;

class KvClient{
    private:
    std::unique_ptr<Kvs::Stub> stub;
    public:
        KvClient(std::shared_ptr<Channel> channel) : stub(Kvs::NewStub(channel)) {}
        int put(const std::string &key, const std::string &value){
            Request request;
            request.set_key(key);
            request.set_value(value);
            Response response;
            ClientContext cxt;
            Status status = stub->put(&cxt,request,&response);
            if(status.ok()){
                std::cout<<response.res()<<std::endl;
                return 0;
            }else{
                // 
                return -1;
            }
        }
        int get(const std::string &key, std::string &value){
            return 0;
        }
        int remove(const std::string &key){
            return 0;
        }
}

# endif