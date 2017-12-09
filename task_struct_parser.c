#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <stdio.h>
#include <string.h>

int ji_hex_to_byte(unsigned char *ji_hex_p, unsigned char *ji_byte_p, int ji_size)
{
    unsigned char ji_byte_vale;

    unsigned char *ji_hex_e = ji_hex_p + ji_size;

    for(; ji_hex_p < ji_hex_e; ji_hex_p += 2, ji_byte_p += 1)
    {
        ji_byte_vale = 0;
        if(*ji_hex_p > '9')
        {
            ji_byte_vale = *ji_hex_p - 87;
        }
        else
        {
            ji_byte_vale = *ji_hex_p - 48;
        }

        ji_byte_vale *= 16;

        if(*(ji_hex_p+1) > '9')
        {
            ji_byte_vale += *(ji_hex_p+1) - 87;
        }
        else
        {
            ji_byte_vale += *(ji_hex_p+1) - 48;
        }

        *ji_byte_p = ji_byte_vale;
    }

    return 0;
}


int ji_json_out(char * ji_field_name, unsigned char * ji_struct_byte,
        int ji_field_offset, int ji_field_size)
{
    printf("{\"name\":\"%s\",", ji_field_name);
    printf("\"offset\":%d,", ji_field_offset);
    printf("\"size\":%d,", ji_field_size);
    printf("\"hex\":\"");

    int i;
    for(i=0; i<ji_field_size; i++)
    {
        printf("%02x", *(ji_struct_byte + ji_field_offset + i));
    }
    printf("\"}");
}

int main(int argc, char *argv[])
{
    int ji_str_len;
    ji_str_len = strlen(argv[1]);

    static unsigned char ji_hex_str[1024 * 10];
    static unsigned char ji_struct_byte[1024 * 10];

    int i =0;
    for(i=0; i<ji_str_len; i++)
    {
        ji_hex_str[i] = argv[1][i];
        ji_struct_byte[i] = 0;
    }

    int ji_struct_size = sizeof(struct task_struct);

    int ji_hex_size = ji_struct_size * 2;

    ji_hex_to_byte(ji_hex_str, ji_struct_byte, ji_hex_size);

    unsigned char *ji_char_p;
    ji_char_p = ji_struct_byte;
    /*for(i=0; i<100; i++)*/
    /*{*/
        /*printf("%02x", *ji_char_p);*/
        /*ji_char_p += 1;*/
    /*}*/

    struct task_struct * ji_p;
    ji_p = ji_struct_byte;

    int ji_field_offset;
    int ji_field_size;
    unsigned char * ji_start = ji_p;
    unsigned char * ji_curr;

    printf("[");

    ji_field_size = sizeof(volatile long);
    ji_curr = &(ji_p->state);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("state", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(void *);
    ji_curr = &(ji_p->stack);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("stack", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(atomic_t);
    ji_curr = &(ji_p->usage);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("usage", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(unsigned int);
    ji_curr = &(ji_p->flags);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("flags", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(unsigned int);
    ji_curr = &(ji_p->ptrace);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("ptrace", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct llist_node);
    ji_curr = &(ji_p->wake_entry);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("wake_entry", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(int);
    ji_curr = &(ji_p->on_cpu);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("on_cpu", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(int);
    ji_curr = &(ji_p->on_rq);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("on_rq", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(int);
    ji_curr = &(ji_p->prio);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("prio", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(int);
    ji_curr = &(ji_p->static_prio);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("static_prio", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(int);
    ji_curr = &(ji_p->normal_prio);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("normal_prio", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(unsigned int);
    ji_curr = &(ji_p->rt_priority);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("rt_priority", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(const struct sched_class *);
    ji_curr = &(ji_p->sched_class);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("sched_class", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct sched_entity);
    ji_curr = &(ji_p->se);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("se", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct sched_rt_entity);
    ji_curr = &(ji_p->rt);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("rt", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct task_group *);
    ji_curr = &(ji_p->sched_task_group);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("sched_task_group", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct hlist_head);
    ji_curr = &(ji_p->preempt_notifiers);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("preempt_notifiers", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(unsigned char);
    ji_curr = &(ji_p->fpu_counter);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("fpu_counter", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(unsigned int);
    ji_curr = &(ji_p->btrace_seq);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("btrace_seq", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(unsigned int);
    ji_curr = &(ji_p->policy);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("policy", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(int);
    ji_curr = &(ji_p->nr_cpus_allowed);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("nr_cpus_allowed", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(cpumask_t);
    ji_curr = &(ji_p->cpus_allowed);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("cpus_allowed", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct sched_info);
    ji_curr = &(ji_p->sched_info);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("sched_info", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct list_head);
    ji_curr = &(ji_p->tasks);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("tasks", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct plist_node);
    ji_curr = &(ji_p->pushable_tasks);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("pushable_tasks", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct mm_struct *);
    ji_curr = &(ji_p->mm);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("mm", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct mm_struct *);
    ji_curr = &(ji_p->active_mm);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("active_mm", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct task_rss_stat);
    ji_curr = &(ji_p->rss_stat);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("rss_stat", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(int);
    ji_curr = &(ji_p->exit_state);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("exit_state", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(int);
    ji_curr = &(ji_p->exit_code);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("exit_code", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(int);
    ji_curr = &(ji_p->exit_signal);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("exit_signal", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(int);
    ji_curr = &(ji_p->pdeath_signal);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("pdeath_signal", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(unsigned int);
    ji_curr = &(ji_p->jobctl);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("jobctl", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(unsigned int);
    ji_curr = &(ji_p->personality);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("personality", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    /*ji_field_size = sizeof(unsigned);*/
    /*ji_curr = &(ji_p->did_exec);*/
    /*ji_field_offset = ji_curr - ji_start;*/
    /*ji_json_out("did_exec", ji_struct_byte, ji_field_offset, ji_field_size);*/
    /*printf(",");*/

    /*ji_field_size = sizeof(unsigned);*/
    /*ji_curr = &(ji_p->in_execve);*/
    /*ji_field_offset = ji_curr - ji_start;*/
    /*ji_json_out("in_execve", ji_struct_byte, ji_field_offset, ji_field_size);*/
    /*printf(",");*/

    ji_field_size = sizeof(pid_t);
    ji_curr = &(ji_p->pid);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("pid", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(pid_t);
    ji_curr = &(ji_p->tgid);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("tgid", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(unsigned long);
    ji_curr = &(ji_p->stack_canary);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("stack_canary", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct task_struct *);
    ji_curr = &(ji_p->real_parent);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("real_parent", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct task_struct *);
    ji_curr = &(ji_p->parent);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("parent", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct list_head);
    ji_curr = &(ji_p->children);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("children", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct list_head);
    ji_curr = &(ji_p->sibling);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("sibling", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct task_struct *);
    ji_curr = &(ji_p->group_leader);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("group_leader", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct list_head);
    ji_curr = &(ji_p->ptraced);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("ptraced", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct list_head);
    ji_curr = &(ji_p->ptrace_entry);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("ptrace_entry", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct pid_link);
    ji_curr = &(ji_p->pids);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("pids", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct list_head);
    ji_curr = &(ji_p->thread_group);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("thread_group", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct list_head);
    ji_curr = &(ji_p->thread_node);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("thread_node", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(struct completion *);
    ji_curr = &(ji_p->vfork_done);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("vfork_done", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(int *);
    ji_curr = &(ji_p->set_child_tid);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("set_child_tid", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(int *);
    ji_curr = &(ji_p->clear_child_tid);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("clear_child_tid", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(cputime_t);
    ji_curr = &(ji_p->utime);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("utime", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(cputime_t);
    ji_curr = &(ji_p->stime);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("stime", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(cputime_t);
    ji_curr = &(ji_p->utimescaled);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("utimescaled", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(cputime_t);
    ji_curr = &(ji_p->stimescaled);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("stimescaled", ji_struct_byte, ji_field_offset, ji_field_size);
    printf(",");

    ji_field_size = sizeof(cputime_t);
    ji_curr = &(ji_p->gtime);
    ji_field_offset = ji_curr - ji_start;
    ji_json_out("gtime", ji_struct_byte, ji_field_offset, ji_field_size);







    printf("]");
    return 0;
}

