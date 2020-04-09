#include<stdio.h>
#include<string.h>
#include"./rc4/rc4.h"

void rc4_test();
void printList(uint8*, int);

int main(void) {
	rc4_test();
	return 0;
}

void rc4_test() {
	const char* content = "123456";
	const char* key = "123456";
	const int len_content = strlen(content);
	const int len_key = strlen(key);
	uint8 dst[len_content];

	RC4 rc;
	rc4_reset(&rc, (uint8*)key, len_key);
	rc4_xor(&rc, (uint8*)content, dst, len_content);

	printList(dst, len_content);
}

void printList(uint8* src, int len) {
	int i;
	for (i = 0; i < len; i++) {
		printf("%d ", src[i]);
	}
	printf("\n\n");
}
