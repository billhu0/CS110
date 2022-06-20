int source[] = {3, 1, 4, 1, 5, 9, 0};
int dest[]   = {1, 1, 1, 1, 1, 1, 0, 0, 0, 0};
// the register pointing to source[0] is t1
// the register pointing to dest[0]   is t2
int main() {
    int k;  // the register representing k is 't0'
    for (k=0; source[k]!=0; k++) {
        dest[k] = source[k];
        // k*4 is represented by t3
        // the address source[k] is represented by t4
        // the value  source[k] is represented by t5

        // the address dest[k] is represented by t6
    }
    return 0;
}

int modified_main(){
    int k;
    for (k=0; source[k]!=0; k += 2){
        dest[k] = 2 * source[k];
    }
    return 0;
}



