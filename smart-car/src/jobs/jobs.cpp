#include <LinkedList.h>

namespace Jobs
{
    typedef void (*Job)();
    typedef bool (*ShouldRun)();

    struct JobDefinition
    {
        Job run;
        Job init;
        ShouldRun should_run;
    };

    LinkedList<Jobs::JobDefinition> jobs = LinkedList<Jobs::JobDefinition>();

    void register_action(Jobs::JobDefinition job)
    {
        jobs.add(job);
    }

    void init()
    {
        int action_size = jobs.size();
        for (int i = 0; i < action_size; i++)
        {
            Jobs::JobDefinition job = jobs.shift();
            job.init();
            jobs.add(job);
        }
    }

    void run()
    {
        int action_size = jobs.size();
        for (int i = 0; i < action_size; i++)
        {
            Jobs::JobDefinition job = jobs.shift();
            if (job.should_run())
            {
                job.run();
            }
            jobs.add(job);
        }
    }
} // namespace Jobs
