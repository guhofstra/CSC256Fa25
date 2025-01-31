import math
import matplotlib.pyplot as plt


# Define the Task class
class Task:
    def __init__(self, id, period, execution_time, deadline):
        self.id = id
        self.period = period
        self.execution_time = execution_time
        self.deadline = deadline
        self.next_arrival = 0
        self.remaining_time = execution_time


# Function to calculate the hyperperiod (LCM of task periods)
def calculate_hyperperiod(tasks):
    def lcm(a, b):
        return abs(a * b) // math.gcd(a, b)

    hyperperiod = tasks[0].period
    for task in tasks[1:]:
        hyperperiod = lcm(hyperperiod, task.period)

    return hyperperiod


# Fixed Priority Scheduling simulation
# Fixed Priority Scheduling simulation
def fixed_priority_scheduling(tasks, hyperperiod):
    tasks.sort(key=lambda x: x.period)  # Sort by priority (lower period = higher priority)
    timeline = []
    deadline_misses = []

    # Initialize task states
    for task in tasks:
        task.next_arrival = 0
        task.remaining_time = task.execution_time

    # Simulate scheduling over the hyperperiod
    for current_time in range(hyperperiod):
        # Check for task arrivals
        for task in tasks:
            if current_time == task.next_arrival:
                if current_time > 0 and task.remaining_time > 0:  # Deadline miss (exclude time 0)
                    deadline_misses.append((task.id, current_time))
                task.remaining_time = task.execution_time
                task.next_arrival += task.period

        # Find the highest-priority ready task
        ready_tasks = [t for t in tasks if t.remaining_time > 0]
        if ready_tasks:
            current_task = ready_tasks[0]  # Highest priority (sorted list)
            current_task.remaining_time -= 1
            timeline.append(current_task.id)
        else:
            timeline.append(-1)  # Idle time

    return timeline, deadline_misses


# Plotting function for Gantt chart and deadline misses
def plot_schedule(timeline, deadline_misses, tasks, hyperperiod):
    colors = ['red', 'green', 'blue']

    plt.figure(figsize=(15, 6))

    # Sort tasks by priority (ascending order of period)
    sorted_tasks = sorted(tasks, key=lambda x: x.period)

    # Gantt chart plot
    plt.subplot(2, 1, 1)
    plt.title('Fixed Priority Scheduling - Gantt Chart')
    plt.xlabel('Time')
    plt.ylabel('Tasks')
    plt.xlim(0, hyperperiod)
    plt.ylim(0, len(tasks) + 1)
    plt.grid(axis='x', linestyle='--')

    # Create a mapping of task IDs to their vertical position (higher priority = higher position)
    task_y_positions = {task.id: len(tasks) - i for i, task in enumerate(sorted_tasks)}

    # Plot tasks
    for time, task_id in enumerate(timeline):
        if task_id != -1:
            color_index = task_id - 1
            plt.barh(task_y_positions[task_id], 1, left=time,
                     color=colors[color_index], edgecolor='black')

    # Set y-tick labels to show task IDs in priority order
    plt.yticks(list(task_y_positions.values()),
               [f"Task {task.id}" for task in sorted_tasks])

    # Deadline misses plot
    plt.subplot(2, 1, 2)
    plt.title('Deadline Misses')
    plt.xlabel('Time')
    plt.ylabel('Task')
    plt.xlim(0, hyperperiod)
    plt.ylim(0, len(tasks) + 1)

    # Plot deadline misses
    for task_id, time in deadline_misses:
        plt.scatter(time, task_y_positions[task_id], color='red', marker='x', s=100)

    # Set y-tick labels for deadline misses
    plt.yticks(list(task_y_positions.values()),
               [f"Task {task.id}" for task in sorted_tasks])

    plt.tight_layout()
    plt.show()


# Example Task Set
tasks = [
    Task(1, 6, 2, 6),  # Task 1: Period=6ms, Execution Time=2ms, Deadline=6ms
    Task(2, 8, 3, 8),  # Task 2: Period=8ms, Execution Time=3ms, Deadline=8ms
    Task(3, 12, 3, 12)  # Task 3: Period=12ms, Execution Time=3ms, Deadline=12ms
]

# Calculate hyperperiod and run simulation
hyperperiod = calculate_hyperperiod(tasks)
timeline, deadline_misses = fixed_priority_scheduling(tasks, hyperperiod)

# Plot results
plot_schedule(timeline, deadline_misses, tasks, hyperperiod)
