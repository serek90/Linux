cmd_/home/serek/programs/githubC/Linux/Linux/HelloModule/hello.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -T ./scripts/module-common.lds --build-id  -o /home/serek/programs/githubC/Linux/Linux/HelloModule/hello.ko /home/serek/programs/githubC/Linux/Linux/HelloModule/hello.o /home/serek/programs/githubC/Linux/Linux/HelloModule/hello.mod.o ;  true