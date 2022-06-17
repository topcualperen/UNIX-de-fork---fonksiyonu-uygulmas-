#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int pid, status, child_pid, c;
	char file_name[30]; // yeni oluþturulacak dosya ismi için buffer oluþturuldu.
	sprintf(file_name, "%s_duzeltilmis", argv[1]);
	if(argc != 2){
		printf("Bir adet dosya ismi vermelisiniz!\n");
		exit(-1);
	}
	pid = fork();
	if(pid == 0){
		FILE *infile = fopen(argv[1], "r");
		if(infile == NULL){
			printf("Dosya acma hatasi!\n");
			exit(-2);
		}
		FILE *outfile = fopen(file_name, "w");
		if(infile == NULL){
			printf("Dosya acma hatasi!\n");
			exit(-3);
		}
		while((c = getc(infile)) != EOF){
			if(c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == '0'){
				putc('*', outfile);		
			}
			else{
				putc(c, outfile);
			}
		}
		fclose(infile);
		fclose(outfile);
		exit(42); // random bir sayýyla çýkýþ yapýldý.
	}
	if(pid > 0){
		child_pid = wait(&status);
		FILE *outfile = fopen(file_name, "a"); //Dosyaya ekleme yapýlacaðý için 'a'(append) kullanýldý.
		fprintf(outfile, "Bu dosya %d numarali islem tarafindan olusturulmustur.\n", child_pid);
		fclose(outfile);
	}
	exit(0);
}
