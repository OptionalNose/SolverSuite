#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	char const *name;
	char const *exe_deps;
} Module;

const Module modules[] = {
	(Module) {
		.name = "common",
	},
	(Module) {
		.name = "parse",
		.exe_deps = "libcommon",
	},
	(Module) {
		.name = "eval",
		.exe_deps = "libparse libcommon",
	}, 
};

const int module_count = (sizeof modules) / (sizeof modules[0]);

const char *dbgstub = "clang -O0 -g src/";
const char *optstub = "clang -O3 src/";

const char *libstub = ".c -DLIB -c -o build/lib";

const char *exestub = ".c -o build/";

int main(void)
{
	int err = 0;
	char *cmdbuffer = NULL;

	for(int i = 0; i < module_count; i++) {
		cmdbuffer = realloc(cmdbuffer, strlen(optstub) + strlen(modules[i].name) * 2 + strlen(libstub) + 1);
		if(!cmdbuffer) {
			fprintf(stderr, "OOM!\n");
			err = 1;
			goto RET;
		}

		cmdbuffer[0] = '\0';
		
		strcat(cmdbuffer, optstub);
		strcat(cmdbuffer, modules[i].name);
		strcat(cmdbuffer, libstub);
		strcat(cmdbuffer, modules[i].name);

		system(cmdbuffer);
	}

	for(int i = 0; i < module_count; i++) {
		int len = strlen(dbgstub) + strlen(modules[i].name) * 2 + strlen(exestub) + 1;
		cmdbuffer = realloc(cmdbuffer, len);
		if(!cmdbuffer) {
			fprintf(stderr, "OOM!\n");
			err = 1;
			goto RET;
		}

		cmdbuffer[0] = '\0';

		strcat(cmdbuffer, dbgstub);
		strcat(cmdbuffer, modules[i].name);
		strcat(cmdbuffer, exestub);
		strcat(cmdbuffer, modules[i].name);

		char const* sep = NULL;
		char const* prev_sep = modules[i].exe_deps;
		while((sep = strchr(modules[i].exe_deps, ' ')) != NULL) {
			len += 3 + (sep - prev_sep);
			cmdbuffer = realloc(cmdbuffer, len);
			if(!cmdbuffer) {
				fprintf(stderr, "OOM!\n");
				err = 1;
				goto RET;
			}

			strcat(cmdbuffer, " -l");
			strncat(cmdbuffer, prev_sep, sep - prev_sep);

			prev_sep = sep + 1;
		}

		if(prev_sep) {
			len += 3 + strlen(prev_sep);
			cmdbuffer = realloc(cmdbuffer, len);
			if(!cmdbuffer) {
				fprintf(stderr, "OOM!\n");
				err = 1;
				goto RET;
			}

			strcat(cmdbuffer, " -l");
			strcat(cmdbuffer, prev_sep);
		}

		system(cmdbuffer);
	}	

RET:
	if(cmdbuffer) free(cmdbuffer);
	return err;
}
