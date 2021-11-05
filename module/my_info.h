#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/cpufreq.h>
#include <linux/mm.h>
#include <linux/version.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/time.h>
#include <linux/smp.h>
#include <asm/processor.h>
#include <linux/utsname.h>
#include <linux/memory.h>
#include <linux/ktime.h>
#include <linux/mm.h>
#include <linux/mmzone.h>
#include <linux/vmstat.h>
// #include <linux/meminfo.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("PEKO");
MODULE_DESCRIPTION("system info");
MODULE_VERSION("1.0");