
int function(char *inbuf, int inlen) {
	char *templ = "NATMWS1001111111";
	char buf[1024];
	char data[9];
	char iv[17];

	int loop = 0;

	loop = inlen / 8;
	if(inlen % 8 != 0) {
		loop++;
	}

	for(int i = 0; i < loop; i++) {
		memset(buf, 0, 1024);
		memset(data, 0, 9);
		memcpy(data, (inbuf+loop*8), 8);

		if(i == 0) {
			sprintf(buf, ...);
			sprintf(buf, ...);
			sprintf(buf, templ, data);
		}
		else if(i == (loop-1)) {
			memset(data, '0x00', 8);
			memcpy(data, (inbuf+loop*8), inlen-loop*8);

			sprintf(buf, ...);
			sprintf(buf, templ, iv);
			printf(buf, templ, data);
			break;
		}
		else {
			sprintf(buf, ...);
			sprintf(buf, templ, iv);
			printf(buf, templ, data);
		}

		write(buf, ...);
		read(buf, ...);

		ptr = buf;
		ptr += 8;
		memset(iv, 0, 17);
		memcpy(iv, ptr, 16);
	}
}
