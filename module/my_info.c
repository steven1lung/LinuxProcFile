#include "my_info.h"

// #if LINUX_VERSION_CODE >= KERNEL_VERSION(5,6,0)
// #define HAVE_PROC_OPS
// #endif

#define procfs_name "my_info"

static struct proc_dir_entry *proc_file;

static int procfile_print(struct seq_file *m,void *v)
{
    seq_printf(m,"==========Version==========\n");
    seq_printf(m,utsname()->sysname);
    seq_printf(m," ");
    seq_printf(m,utsname()->release);
    seq_printf(m,"\n\n");


    seq_printf(m,"============CPU============\n");
    unsigned cpu = get_cpu();
    struct cpuinfo_x86 *info;
    info=&cpu_data(cpu);
    seq_printf(m,"processor\t: %u\n",cpu);
    //model name
    seq_printf(m,"model name\t: ");
    if(info->x86_model_id[0]) seq_printf(m,"%s",info->x86_model_id);
    else seq_printf(m,"%d86",info->x86);

    seq_printf(m,"\nphysical id\t: %d\n",info->phys_proc_id);
    seq_printf(m,"core id\t\t: %d\n",info->cpu_core_id);


    seq_printf(m,"cpu cores\t: %u\n",info->x86_max_cores);
    seq_printf(m,"cache size\t: %d KB\n",info->x86_cache_size);
    seq_printf(m,"clflush size\t: %u\n",info->x86_clflush_size);
    seq_printf(m,"cache_alignment\t: %d\n",info->x86_cache_alignment);
    seq_printf(m,"address sizes\t: %u bits physical, %u bits virtual\n",info->x86_phys_bits,info->x86_virt_bits);
    seq_printf(m,"\n\n");

    seq_printf(m,"==========Memory==========\n");
    seq_printf(m,"Memtotal\t: %d\n",info->cpu_core_id);
    seq_printf(m,"MemFree\t\t: %d\n",info->cpu_core_id);
    seq_printf(m,"Buffers\t\t: %d\n",info->cpu_core_id);
    seq_printf(m,"Active\t\t: %d\n",info->cpu_core_id);
    seq_printf(m,"Inactive\t: %d\n",info->cpu_core_id);
    seq_printf(m,"Shmen id\t: %d\n",info->cpu_core_id);
    seq_printf(m,"Dirty\t\t: %d\n",info->cpu_core_id);
    seq_printf(m,"Writeback\t: %d\n",info->cpu_core_id);
    seq_printf(m,"KernelStack\t: %d\n",info->cpu_core_id);
    seq_printf(m,"PageTables\t: %d\n",info->cpu_core_id);
    seq_printf(m,"\n\n");


    seq_printf(m,"============Time============\n");
    s64 uptime;
    uptime=ktime_to_ns(ktime_get_boottime());
    u64 idletime;
    idletime=get_cpu_idle_time(cpu,NULL,NULL);
    seq_printf(m,"Uptime\t\t: %llu (s)\n",uptime/NSEC_PER_SEC);
    seq_printf(m,"Idletime\t: %llu (s)\n",idletime/USEC_PER_SEC);
    seq_printf(m,"\n\n");


    put_cpu();
    return 0;
}

static int proc_open(struct inode *inode,struct file *file)
{
    return single_open(file,procfile_print,NULL);
}

static const struct file_operations proc_file_fops=
{
    .owner = THIS_MODULE,
    .open = proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};



static int __init init_my_module(void)
{
    proc_file=proc_create(procfs_name,0644,NULL,&proc_file_fops);

    if(proc_file==NULL)
    {
        proc_remove(proc_file);
        printk(KERN_ALERT "Error: Cound not initialize /proc/%s\n",procfs_name);
        return -ENOMEM;
    }



    printk(KERN_INFO "/proc/%s created\n",procfs_name);
    return 0;
}

static void __exit exit_my_module(void)
{
    proc_remove(proc_file);
    printk(KERN_INFO "/proc/%s removed\n",procfs_name);
}

module_init(init_my_module);
module_exit(exit_my_module);
