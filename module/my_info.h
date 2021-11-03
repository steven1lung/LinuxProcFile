#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/cpufreq.h>
#include <linux/mm.h>
#include <linux/version.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/utsname.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("PEKO");
MODULE_DESCRIPTION("system info");
MODULE_VERSION("1.0");