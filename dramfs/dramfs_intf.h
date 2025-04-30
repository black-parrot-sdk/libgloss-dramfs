
#ifndef DRAMFS_INTF_H
#define DRAMFS_INTF_H

// Exit routine: exit() calls this routine
// Definition provided externally by user
extern void dramfs_exit(int);

// Utility to print a char to console
// Definition provided externally by user
extern void dramfs_sendchar(int);

// Utility to get a char from console
// Definition provided externally by user
extern int dramfs_getchar(void);

#endif
