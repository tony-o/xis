#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xis.h"

#define VERSION 0

static void repl();
static void run_file(const char*);

int main(int argc, const char* argv[]) {
  if(argc == 1){
    repl();
  } else if (argc == 2) {
    run_file(argv[1]);
  } else {
    printf("Usage: xis <file>\n");
    printf("   or: xis\n");
    exit(255);
  }
  return 0;
}

static void repl(){
  VM vm;
  vm_init(&vm);

  char line[1024];

  printf(" ██▀███   ▄▄▄       ▄████▄   ▄████▄   ▒█████   ▒█████   ███▄    █\n");
  printf("▓██ ▒ ██▒▒████▄    ▒██▀ ▀█  ▒██▀ ▀█  ▒██▒  ██▒▒██▒  ██▒ ██ ▀█   █\n");
  printf("▓██ ░▄█ ▒▒██  ▀█▄  ▒▓█    ▄ ▒▓█    ▄ ▒██░  ██▒▒██░  ██▒▓██  ▀█ ██▒\n");
  printf("▒██▀▀█▄  ░██▄▄▄▄██ ▒▓▓▄ ▄██▒▒▓▓▄ ▄██▒▒██   ██░▒██   ██░▓██▒  ▐▌██▒\n");
  printf("░██▓ ▒██▒ ▓█   ▓██▒▒ ▓███▀ ░▒ ▓███▀ ░░ ████▓▒░░ ████▓▒░▒██░   ▓██░\n");
  printf("░ ▒▓ ░▒▓░ ▒▒   ▓▒█░░ ░▒ ▒  ░░ ░▒ ▒  ░░ ▒░▒░▒░ ░ ▒░▒░▒░ ░ ▒░   ▒ ▒\n");
  printf("  ░▒ ░ ▒░  ▒   ▒▒ ░  ░  ▒     ░  ▒     ░ ▒ ▒░   ░ ▒ ▒░ ░ ░░   ░ ▒░\n");
  printf("  ░░   ░   ░   ▒   ░        ░        ░ ░ ░ ▒  ░ ░ ░ ▒     ░   ░ ░\n");
  printf("   ░           ░  ░░ ░      ░ ░          ░ ░      ░ ░           ░\n");
  printf("                   ░        ░\n");



  printf("\nstarting repl for xis version %d\n\n", VERSION);
  int q = 1;
  for(;q;){
    printf("o> ");
    if(!fgets(line, sizeof(line), stdin)){
      printf("\n");
      break;
    }
    if(line[0] == '\\'){
      q = line[1] == 'q' ? 0 : 1;
      break;
    }
    line[strlen(line)-1] = '\0';
    vm_interpret(&vm, line);
  }
  printf("cleaning up...\n");
  vm_free(&vm);
  printf("l8r skater!\n");
}

static void run_file(const char* path){
  FILE* f = fopen(path, "rb");
  if(f == NULL){
    fprintf(stderr, "Unable to open file: %s\n", path);
    exit(1);
  }
  fseek(f, 0L, SEEK_END);
  size_t fs = ftell(f);
  rewind(f);

  char* buffer = (char*)malloc(fs+1);
  if(buffer == NULL){
    fprintf(stderr, "Not enough memory to read: %s\n", path);
    fclose(f);
    exit(1);
  }
  size_t br = fread(buffer, sizeof(char), fs, f);
  if(br < fs){
    fprintf(stderr, "Failed to read file: %s\n", path);
    fclose(f);
    exit(1);
  }
  buffer[br] = '\0';
  fclose(f);

  VM vm;
  vm_init(&vm);

  vm_interpret(&vm, buffer);

  vm_free(&vm);
}
