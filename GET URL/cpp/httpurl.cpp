/*
 * IPWorks SSL 2022 C++ Edition - Demo Application
 *
 * Copyright (c) 2023 /n software inc. - All rights reserved. - www.nsoftware.com
 *
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/ipworksssl.h"
#define LINE_LEN 100

class MyHTTP : public HTTP
{
public:
	virtual int FireTransfer(HTTPTransferEventParams *e)
	{
		//this may be avoided altogether if the LocalFile property is used
		fwrite(e->Text, sizeof(char), e->lenText, stdout);
		return 0;
	}

	virtual int FireSSLServerAuthentication(HTTPSSLServerAuthenticationEventParams *e)
	{
		if (e->Accept) return 0;
		printf("Server provided the following certificate:\nIssuer: %s\nSubject: %s\n",
			e->CertIssuer, e->CertSubject);
		printf("The following problems have been determined for this certificate: %s\n", e->Status);
		printf("Would you like to continue anyways? [y/n] ");
		if (getchar() == 'y') e->Accept = true;
		else exit(0);
		return 0;
	}
};

int main(int argc, char **argv)
{

	if (argc < 2)
	{
		fprintf(stderr, "usage: httpurl url\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "  url  the url to fetch\n");
		fprintf(stderr, "\nExample: httpurl https://www.google.com\n\n");
		printf("Press enter to continue.");
		getchar();

	}
	else
	{
		MyHTTP http;

		http.SetFollowRedirects(2);
		int ret_code = http.Get(argv[1]);

		if (ret_code)     // Got an error.  The user is done.
		{
			printf("\nError: %d", ret_code);
			if (http.GetLastError())
			{
				printf(" \"%s\"\n", http.GetLastError());
			}
		}

		fprintf(stderr, "\npress <return> to continue...\n");
		getchar();
		exit(ret_code);
		return 0;
	}

}








