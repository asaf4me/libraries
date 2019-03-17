#include "threadpool.h"

void usage()
{
    printf("Usage: server <port> <pool-size> <max-number-of-request>");
}

threadpool *create_threadpool(int num_threads_in_pool)
{
    if (num_threads_in_pool < 0 || num_threads_in_pool > MAXT_IN_POOL)
    {
        usage();
        return NULL;
    }
    threadpool *pool = (threadpool *)malloc(sizeof(threadpool));
    if (pool == NULL)
    {
        perror("malloc");
        return NULL;
    }
    pool->num_threads = num_threads_in_pool;
    pool->qsize = 0;
    pool->threads = (pthread_t *)malloc(pool->num_threads * sizeof(pthread_t));
    if (pool == NULL)
    {
        perror("error: <sys_call>\n");
        destroy_threadpool(pool);
        return NULL;
    }
    pool->qhead = NULL;
    pool->qtail = NULL;
    pthread_mutex_init(&pool->qlock, NULL);
    pthread_cond_init(&pool->q_empty, NULL);
    pthread_cond_init(&pool->q_not_empty, NULL);
    for (int i = 0; i < pool->num_threads; i++)
    {
        if (pthread_create(&pool->threads[i], NULL, do_work, (void *)pool))
        {
            perror("error: <sys_call>\n");
            destroy_threadpool(pool);
            exit(-1);
        }
    }
    pool->shutdown = pool->dont_accept = 0;
    return pool;
}

void dispatch(threadpool *from_me, dispatch_fn dispatch_to_here, void *arg)
{
    pthread_mutex_lock(&from_me->qlock);
    if (from_me->dont_accept == 1)
        return;
    from_me->qsize++;
    work_t *work = (work_t *)malloc(sizeof(work_t));
    if (work == NULL)
    {
        perror("error: <sys_call>\n");
        destroy_threadpool(from_me);
    }
    work->arg = arg;
    work->routine = dispatch_to_here;
    work->next = NULL;
    if (from_me->qhead == NULL)
    {
        from_me->qhead = from_me->qtail = work;
        pthread_mutex_unlock(&from_me->qlock);
        return;
    }
    from_me->qtail->next = work;
    from_me->qtail = work;
    pthread_mutex_unlock(&from_me->qlock);
}

work_t *dequeue(threadpool *pool)
{
    if (pool == NULL || pool->qhead == NULL) /* if the pool is not init, or the queue is empty, return NULL */
        return NULL;
    work_t *temp = pool->qhead;      /* store the head */
    pool->qhead = pool->qhead->next; /* move the head down */
    if (pool->qhead == NULL)         /* if the head is NULL, then the tail also need to be NULL */
        pool->qtail = NULL;
    return temp;
}

void *do_work(void *p) // To do: add mutex, verify for signals and identify when to kill the proccess
{
    threadpool *pool = (threadpool *)p;
    while (true)
    {
        if (pool->shutdown == 1)
        {
            pthread_exit(NULL);
            break;
        }
        pthread_mutex_lock(&(pool->qlock));
        while (pool->qsize == 0 && pool->shutdown != 1)
            pthread_cond_wait(&(pool->q_empty), &(pool->qlock));

        if (pool->shutdown == 1)
        {
            pthread_exit(NULL);
            break;
        }
        if(pool->qsize == 0 && pool->dont_accept == 1)
        {

        }
        work_t *worker = dequeue(pool);
        pool->qsize--;
        pthread_mutex_unlock(&(pool->qlock)); /* unlock */
        (*(worker->routine))(worker->arg);
    }
    pthread_mutex_unlock(&(pool->qlock));
    pthread_exit(NULL);
    return (NULL);
}

void destroy_threadpool(threadpool *destroyme) // Debug and test with valgring
{
    if (destroyme == NULL)
        return;
    destroyme->dont_accept = 1;  /* rise up the dont accept flag */
    while (destroyme->qsize > 0) /* wait for work queue to get empty */
    {
        if ((pthread_cond_broadcast(&(destroyme->q_empty)) != 0)) /* wake up all worker threads */
            break;
        for (int i = 0; i < destroyme->num_threads; i++) /* Join all worker thread */
        {
            if (pthread_join(destroyme->threads[i], NULL) != 0)
            {
                perror("error: <sys_call>\n");
                exit(1);
            }
        }
    }
    destroyme->shutdown = 1;
    if (destroyme->threads)
    {
        if (destroyme->qhead != NULL)
        {
            work_t *p = destroyme->qhead;
            work_t *temp;
            while (p)
            {
                temp = p;
                p = p->next;
                free(temp);
            }
        }
        free(destroyme->threads);
    }
    pthread_mutex_destroy(&(destroyme->qlock));
    pthread_cond_destroy(&(destroyme->q_empty));
    pthread_cond_destroy(&(destroyme->q_not_empty));
    free(destroyme);
}
