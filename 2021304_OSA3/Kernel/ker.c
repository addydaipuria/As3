#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/sched.h>
#include<linux/moduleparam.h>
#include<linux/unistd.h>
#include<linux/types.h>
#include<linux/syscalls.h>

int score=-1;
MODULE_LICENSE("GPL");
module_param(score,int,0);

static int __init walter(void){
    struct task_struct *jesse;
    jesse=pid_task(find_vpid(score),PIDTYPE_PID);

    if(!jesse){
        printk("INVALID INPUT\n");
        return EINVAL;
    }
    printk("Process Name: %s\n",jesse->comm);
    printk("PID UID %d || %d\n",jesse->pid,jesse->cred->uid.val);
    printk("Group ID: %d\n",jesse->group_leader->pid);
    return 0;
}

static void __exit mike(void){
    printk("System call close\n");
}
module_init(walter);
module_exit(mike);