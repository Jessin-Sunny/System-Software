void roundrobin()
{
    int i,j,flag,remain=n,sys_time;
    initialize();
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(temp[j].arrival > temp[j+1].arrival)
            {
                temp_p=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_p;
            }
        }
    }
    int ready[30],count=0;
    for(sys_time=0,i=0;remain!=0;)
    {
        if(temp[i].remaining <= slice && temp[i].remaining > 0)
        {
            sys_time+=temp[i].remaining;
            temp[i].remaining=0;
            flag=1;
        }
        else if(temp[i].remaining > 0)
        {
            sys_time+=slice;
            temp[i].remaining=temp[i].remaining-slice;
        }
        if(temp[i].remaining == 0 && flag == 1)
        {
            remain--;
            temp[i].completion=sys_time;
            temp[i].turnaround=temp[i].completion-temp[i].arrival;
            temp[i].waiting=temp[i].turnaround-temp[i].burst;
            temp[i].completed=1;
            flag=0;
        }
        int m=0;
        for(j=0;j<n;j++)
        {
            if(temp[j].arrival <= sys_time && temp[j].remaining != 0)
            {
                ready[m++]=j;
            }
        }
        if(m > 0)
        {
            count=(count+1)%m;
            i=ready[count];
        }
        else
        {
            sys_time++;
        }
    }
    display(temp);
}
