#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN 2048


char *trim(char *);
void display_matrix(char **, int x, int y);
void display_matrix_int(int **, int x, int y);
char *split(char **);
int main(int argc, char **argv) {

    FILE *f;
    int c, i, xi, yi, j;
    int **inmatrix;
    int **drainmatrix;
    char **outmatrix;
    char *tmp;
    char cur, cur2;
    int cases=0;
    int x, y=0, ch=0, cc=1,done=0;
    char tmpbuf1[BUFLEN];
    char *tbp=tmpbuf1;
	 char *tbpo;
    char map[26];
    if (argc!=2) {
		fprintf(stderr,"Usage: %s <file>\n",argv[0]);
		exit(1);
    }
	 
    f=fopen(argv[1],"r");
    fgets(tmpbuf1,BUFLEN-1,f);
    trim(tmpbuf1);
    cases=atoi(tmpbuf1);
#ifdef DEBUG
    printf("%d\n",cases);
#endif
    for (i=0;i<cases;i++) {
		printf("Case #%d:\n",i+1);
		fgets(tmpbuf1,BUFLEN-1,f);
		trim(tmpbuf1);
		if (sscanf(tmpbuf1,"%i %i",&y, &x)!=2) {
		  fprintf(stderr,"Error on input line %s.  Expecting 'int int'\n",
					 tmpbuf1);
		  exit(-1);
		}
#ifdef DEBUG
		printf("X: %d Y: %d\n",x,y);
#endif
		inmatrix=(int **)calloc(y,sizeof(int *));
		outmatrix=(char **)calloc(y,sizeof(char *));
		drainmatrix=(int **)calloc(y,sizeof(int *));
		for (yi=0;yi<y;yi++) {
		  inmatrix[yi]=(int *)calloc(x,sizeof(int));
		  drainmatrix[yi]=(int *)calloc(x,sizeof(int));
		  outmatrix[yi]=(char *)calloc(x,sizeof(char));
		  memset(outmatrix[yi],'*',x);
		  fgets(tmpbuf1,BUFLEN-1,f);
		  trim(tmpbuf1);
		  tbpo=tbp=(char *)malloc(strlen(tmpbuf1)+1);
		  strcpy(tbp,tmpbuf1);
		  for (xi=0;xi<x;xi++) {
			 tmp=split(&tbp);
			 inmatrix[yi][xi]=atoi(tmp);
		  }
		  free(tbpo);
		}
		/* Who drains where */
		cur='A';
		for (yi=0;yi<y;yi++) {
		  for (xi=0;xi<x;xi++) {
			 cc=((yi)*x)+(xi);
			 ch=inmatrix[yi][xi];
			 
			 if (yi!=0) {
				if (inmatrix[yi-1][xi]<ch) {
				  drainmatrix[yi][xi]=((yi-1)*x)+(xi);
				  ch=inmatrix[yi-1][xi];
				}
			 }
			 if (xi!=0) {
				if (inmatrix[yi][xi-1]<ch) {
				  drainmatrix[yi][xi]=(((yi)*x)+(xi-1));
				  ch=inmatrix[yi][xi-1];
				}
			 }
			 if (xi!=x-1) {
				if (inmatrix[yi][xi+1]<ch) {
				  drainmatrix[yi][xi]=(((yi)*x)+(xi+1));
				  ch=inmatrix[yi][xi+1];
				}
			 }
			 if (yi!=y-1) {
				if (inmatrix[yi+1][xi]<ch) {
				  drainmatrix[yi][xi]=((yi+1)*x)+(xi);
				  ch=inmatrix[yi+1][xi];
				}
			 }
			 if (ch==inmatrix[yi][xi]) {
				outmatrix[yi][xi]=cur;
				drainmatrix[yi][xi]=-1;
				cur++;
			 }
		  }	   
		}
#ifdef DEBUG
		display_matrix_int(drainmatrix,x,y);
		display_matrix_int(inmatrix,x,y);
		display_matrix(outmatrix,x,y);
#endif
		done=0;
		while (done==0) {
		  done=1;
		  for (yi=0;yi<y;yi++) {
			 for (xi=0;xi<x;xi++) {
				cc=((yi)*x)+(xi);
				if (outmatrix[yi][xi]!='*') {
				  /* Find all neighbors draining to me - same number */
				  if (yi!=0) {
					 if (drainmatrix[yi-1][xi]==cc && 
						  outmatrix[yi-1][xi]=='*') {
						outmatrix[yi-1][xi]=outmatrix[yi][xi];
						done=0;
					 }
				  }
				  if (xi!=0) {
					 if (drainmatrix[yi][xi-1]==cc &&
						  outmatrix[yi][xi-1]=='*') {
						outmatrix[yi][xi-1]=outmatrix[yi][xi];
						done=0;
					 }
				  }
				  if (xi!=x-1) {
					 if (drainmatrix[yi][xi+1]==cc &&
						  outmatrix[yi][xi+1]=='*') {
						outmatrix[yi][xi+1]=outmatrix[yi][xi];
						done=0;
					 }
				  }
				  if (yi!=y-1) {
					 if (drainmatrix[yi+1][xi]==cc &&
						  outmatrix[yi+1][xi]=='*') {
						outmatrix[yi+1][xi]=outmatrix[yi][xi];
						done=0;
					 }
				  }
				} 
			 }
		  }
#ifdef DEBUG
		  display_matrix(outmatrix,x,y);
#endif
		}
		/* One last time to go into lexographic order */
		j=cur-'A';
		cur2=0;
		memset(map,'*',j);
		map[j]='\0';
		for(yi=0;yi<y;yi++) {
		  for (xi=0;xi<x;xi++) {
			 if (map[outmatrix[yi][xi]-'A']=='*') {
				map[outmatrix[yi][xi]-'A']='a'+cur2;
				outmatrix[yi][xi]='a'+cur2;
				cur2++;
			 } else {
				outmatrix[yi][xi]=map[outmatrix[yi][xi]-'A'];
			 }
		  }
		}
#ifdef DEBUG
		for (cur2=0;cur2<j;cur2++) {
		  printf("%c = %c\n",'A'+cur2,map[cur2]);
		}
#endif	
		display_matrix(outmatrix,x,y);
    	for (yi=0;yi<y;yi++) {
		  free(inmatrix[yi]);
		  free(outmatrix[yi]);
		  free(drainmatrix[yi]);
		}
		free(inmatrix);
		free(outmatrix);
		free(drainmatrix);
		
    }    
}

void display_matrix_int(int **matrix, int x, int y) {
    int i, j;
    for (i=0;i<y;i++) {
		for (j=0;j<x;j++) {
		  printf("%d ",matrix[i][j]);
		}
		printf("\n");
    }
#ifdef DEBUG
    printf("---\n");
#endif
}

void display_matrix(char **matrix, int x, int y) {
  int i, j;
  for (i=0;i<y;i++) {
	 for (j=0;j<x;j++) {
		printf("%c ",matrix[i][j]);
	 }
	 printf("\n");
  }
#ifdef DEBUG
  printf("---\n");
#endif
}

char *trim(char *input) {
  if (input[strlen(input)-2]=='\r') {
	 input[strlen(input)-2]='\0';
  } else if (input[strlen(input)-1]=='\n') {
	 input[strlen(input)-1]='\0';
  }
  return input;
}

char *split(char **ret) {
  char *o, *r;
  o=*ret;
  while (*o==' ')
	 o++;
  r=o;
  while (*o && *o!=' ')
	 o++;
  if (*o!='\0')
	 *o++='\0';
  else
	 *o='\0';
  *ret=o;
  return r;
}
