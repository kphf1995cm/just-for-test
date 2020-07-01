# include<iostream>
# include"api-group.h"
# include"storage.h"

int main(){
    // init storage config
    Storage* s=Storage::getInstance();
    s->init();
    // 
    return 0;
}