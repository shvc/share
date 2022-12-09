#include <string.h>
#include <syslog.h>

int main(int argc, char** argv)
{
	char msg[64];
	if(argc > 1) {
		strcpy(msg, argv[1]);
	} 
	else {
		strcpy(msg, "defautl message");
	}
	openlog("testsyslog", LOG_CONS | LOG_PID, 0);

	syslog(LOG_USER | LOG_INFO,   "LOG_USER | LOG_INFO  : %s genarate %s\n", argv[0], msg);
	syslog(LOG_USER | LOG_NOTICE, "LOG_USER | LOG_NOTICE: %s genarate %s\n", argv[0], msg);
	syslog(LOG_USER | LOG_ERR,    "LOG_USER | LOG_ERR   : %s genarate %s\n", argv[0], msg);
	syslog(LOG_USER | LOG_DEBUG,  "LOG_USER | LOG_DEBUG : %s genarate %s\n", argv[0], msg);

	syslog(LOG_MAIL | LOG_INFO,   "LOG_MAIL | LOG_INFO  : %s genarate %s\n", argv[0], msg);
	syslog(LOG_MAIL | LOG_NOTICE, "LOG_MAIL | LOG_NOTICE: %s genarate %s\n", argv[0], msg);
	syslog(LOG_MAIL | LOG_ERR,    "LOG_MAIL | LOG_ERR   : %s genarate %s\n", argv[0], msg);
	syslog(LOG_MAIL | LOG_DEBUG,  "LOG_MAIL | LOG_DEBUG : %s genarate %s\n", argv[0], msg);

	syslog(LOG_FTP | LOG_INFO,   "LOG_FTP | LOG_INFO  : %s genarate %s\n", argv[0], msg);
	syslog(LOG_FTP | LOG_NOTICE, "LOG_FTP | LOG_NOTICE: %s genarate %s\n", argv[0], msg);
	syslog(LOG_FTP | LOG_ERR,    "LOG_FTP | LOG_ERR   : %s genarate %s\n", argv[0], msg);
	syslog(LOG_FTP | LOG_DEBUG,  "LOG_FTP | LOG_DEBUG : %s genarate %s\n", argv[0], msg);

	closelog();
	return 0;
}

