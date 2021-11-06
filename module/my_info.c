#include "my_info.h"


#define procfs_name "my_info"

static struct proc_dir_entry *proc_file;

static int procfile_print(struct seq_file *m,void *v)
{
    seq_printf(m,"==========Version==========\n");
    seq_printf(m,utsname()->sysname);
    seq_printf(m," version ");
    seq_printf(m,utsname()->release);
    seq_printf(m,"\n\n");


    seq_printf(m,"============CPU============\n");
    unsigned cpu = get_cpu();
    struct cpuinfo_x86 *info;
    info=&cpu_data(cpu);
    unsigned iter=0;

    for(iter=0; iter<info->booted_cores; iter++)
    {
        struct cpuinfo_x86 *info_iter;
        info_iter=&cpu_data(iter);
        seq_printf(m,"processor\t: %u\n",iter);
        //model name
        seq_printf(m,"model name\t: ");
        if(info_iter->x86_model_id[0]) seq_printf(m,"%s",info_iter->x86_model_id);
        else seq_printf(m,"%d86",info_iter->x86);

        seq_printf(m,"\nphysical id\t: %d\n",info_iter->phys_proc_id);
        seq_printf(m,"core id\t\t: %d\n",info_iter->cpu_core_id);


        seq_printf(m,"cpu cores\t: %u\n",info_iter->booted_cores);
        seq_printf(m,"cache size\t: %d KB\n",info_iter->x86_cache_size);
        seq_printf(m,"clflush size\t: %u\n",info_iter->x86_clflush_size);
        seq_printf(m,"cache_alignment\t: %d\n",info_iter->x86_cache_alignment);
        seq_printf(m,"address sizes\t: %u bits physical, %u bits virtual\n\n",info_iter->x86_phys_bits,info_iter->x86_virt_bits);
    }


    seq_printf(m,"\n");



    seq_printf(m,"==========Memory==========\n");
    struct sysinfo i;
    si_meminfo(&i);
    int lru;

    unsigned long pages[NR_LRU_LISTS];
    for(lru = LRU_BASE; lru<NR_LRU_LISTS; lru++)
        pages[lru]=global_node_page_state(NR_LRU_BASE+lru);
    // si_swapinfo(&i);
    seq_printf(m,"Memtotal\t: %lu kB\n",i.totalram);
    seq_printf(m,"MemFree\t\t: %lu kB\n",i.freeram);
    seq_printf(m,"Buffers\t\t: %lu kB\n",i.bufferram);
    seq_printf(m,"Active\t\t: %lu kB\n",pages[LRU_ACTIVE_ANON]+pages[LRU_ACTIVE_FILE]);
    seq_printf(m,"Inactive\t: %lu kB\n",pages[LRU_INACTIVE_ANON]+pages[LRU_INACTIVE_FILE]);
    seq_printf(m,"Shmen id\t: %lu kB\n",i.sharedram);
    seq_printf(m,"Dirty\t\t: %lu kB\n",global_node_page_state(NR_FILE_DIRTY));
    seq_printf(m,"Writeback\t: %lu kB\n",global_node_page_state(NR_WRITEBACK));
    seq_printf(m,"KernelStack\t: %lu kB\n",global_zone_page_state(NR_KERNEL_STACK_KB));
    seq_printf(m,"PageTables\t: %lu kB\n",global_zone_page_state(NR_PAGETABLE));
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
