# experimental-data-and-source-code
The **main** contains large-scale instances with 20 machines, while the remaining instances are in **UMRSRC**.

All test instances are stored in TXT format, and each file follows a uniform naming convention: M{m}_N{n}_P1_P99_S1_S{Max_st}_alpha{α}_Rf{Rf}_NA.txt. In this, m represents the number of machines, n represents the maximum setup time, α represents the resource scale control factor, Rf represents the release time factor, and NA represents the case number. For example, M2_N6_P1_P99_S1_S9_alpha0.05_Rf0.2_1.txt represents a test with 2 machines, 6 jobs, processing time range of [1,99], setup time range of [1,9], and resource scale control factor and release time factor of 0.05 and 0.2, respectively, for the first case. 

Each instance file contains the following metadata:

budget (the given non-renewable resource limit U)
per_unit_time_cost_of_each_machine (the resource consumption per unit time for each machine lk)
job_processing_time_on_each_machine (the processing time of the job pjk)
per_unit_time_release_of_each_job (the release time per unit of each job rj)
per_unit_setup_time_of_each_machine (the setup time per unit of each job on each machine sijk)
