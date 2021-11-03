#include "my_info.h"

// #if LINUX_VERSION_CODE >= KERNEL_VERSION(5,6,0)
// #define HAVE_PROC_OPS
// #endif

#define procfs_name "my_info"

static struct proc_dir_entry *proc_file;

static ssize_t procfile_read(struct file *filePointer, char __user *buffer, size_t buffer_length, loff_t *offset)
{
    // char *s="==========Version==========\n"+utsname()->sysname;
    char *ver=utsname()->version;
    char *sys=utsname()->sysname;
    char *rel=utsname()->release;

    // strcat(sys,ver);




    char *s=sys;
    int len =sizeof(s);
    ssize_t ret = len;

    if(*offset>=len || copy_to_user(buffer,s,len))
    {
        pr_info("copy_to_user failed\n");
        ret = 0;
    }
    else
    {
        pr_info("procfile read %s\n", filePointer->f_path.dentry->d_name.name);
        *offset += len;
    }
    return ret;
}

static int procfile_print(struct seq_file *m,void *v)
{
    seq_printf(m,"==========Version==========\n");
    seq_printf(m,utsname()->sysname);
    seq_printf(m," ");
    seq_printf(m,utsname()->release);
    // seq_printf(m," ");
    // seq_printf(m,utsname()->version);
    seq_printf(m,"\n\n");
    seq_printf(m,"============CPU============\n");


    return 0;
}

static int proc_open(struct inode *inode,struct file *file)
{
    return single_open(file,procfile_print,NULL);
}

// #ifdef HAVE_PROC_OPS
// static const struct proc_ops proc_file_fops = {
//     .proc_read = procfile_read,
// };
// #else
static const struct file_operations proc_file_fops=
{
    .owner = THIS_MODULE,
    .open = proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};
// #endif

// static void *my_seq_start(struct seq_file *s,loff_t *pos){
//     static unsigned long coutner =0;

//     //beginning of seq
//     if(*pos==0){

//         return &counter;
//     }
// }


static int __init init_my_module(void)
{
    proc_file=proc_create(procfs_name,0644,NULL,&proc_file_fops);

    if(proc_file==NULL)
    {
        proc_remove(proc_file);
        printk(KERN_ALERT "Error: Cound not initialize /proc/%s\n",procfs_name);
        return -ENOMEM;
    }

    // proc_file->read_proc=procfile_read;
    // proc_file->ower=THIS_MODULE;
    // proc_file->mode=S_IFREG | S_IRUGO;
    // proc_file->uid = 0;
    // proc_file->gid = 0;
    // proc_file->size = 37;

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
