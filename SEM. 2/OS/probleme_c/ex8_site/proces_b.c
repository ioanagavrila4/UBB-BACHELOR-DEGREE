  #include <time.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <sys/types.h>
  #include <sys/wait.h>
  #include <sys/stat.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <string.h>
int main(int argc, char *argv[]){
      if(argc < 2){
          perror("Please put some arguments!");
          exit(1);
      }
      char *buf;
      int len;
      int i = 1;
      char *myfifo1 = "./myfifo1";
      int f_read = open(myfifo1, O_RDONLY);
      if(-1 == f_read){
          perror("Error on opening a fifo");
          exit(1);
      }
      char new_string[1000];
      char conc_string[1000];
      while(1){
        //prima oara citim lungimea - argc ul
        if(read(f_read, &len, sizeof(int)) < 0){
            perror("error on reading the length of the vector");
            exit(1);
        }
        if(len < 0){
            break;
        }
        buf = malloc((len+1)*sizeof(char));
        int read_bytes = 0;
        while(read_bytes < len){
            int k;
            if(k = read(f_read, buf + read_bytes, (len-read_bytes) * sizeof(char)) > 0){
        read_bytes = k;
            }
        }
        int i;
        for(i = 0; i < len; i++) {
            if(buf[i] <= 'z' && buf[i] >= 'a'){
                buf[i] += 'A'-'a';
            }

        }
          buf[len] = 0;
            close(f_read);


    }
      for(int i = 0; i < len; i++){
        printf("%c", buf[i]);

      }
      return 0;
}
