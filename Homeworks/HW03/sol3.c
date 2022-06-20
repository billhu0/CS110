#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str1[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
int str2[] = {3,4,5,10,11,12,13};
int len1 = 13, len2 = 7;

int main1(){
    int result = 0;
    for (int i = 0; i < len1; i++){
        for (int j = 0; j < len2; j++){
            int curr_len = 0;
            while (i+curr_len < len1 && j+curr_len < len2 && str1[i+curr_len] == str2[j+curr_len]){
                curr_len++;
            }
            if (curr_len >= result) result = curr_len;
        }
    }
    printf("%d\n", result);
    return 0;
}

int main(){
    int result = 0;
    int i = 0, j = 0;
    // in loop 1
    while(i < len1){
        // in loop 2
        j = 0;
        while (j < len2){
            int len = 0;
            // in loop 3
            while (i+len < len1 && j+len < len2 && str1[i+len] == str2[j+len]){
                len++;
            }
            // outloop 3
            if (len > result) result = len;
            j++;
        }
        // outloop 2
        i++;
    }
    // outloop 1
    printf("%d\n", result);
    return 0;
}

