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

    void register_action(JobDefinition action);
    void init();
    void run();
} // namespace Jobs
