struct station {
	int available_seats;
	int waiting_students;
	int next_ticket;
	int next_student;
	pthread_mutex_t lock;
	pthread_cond_t bus_arrive_cond;
	pthread_cond_t bus_loaded_cond;
};

void
station_init(struct station *station)
{
	station->waiting_students = 0;
	station->available_seats = 0;
	station->next_ticket = 1;
	station->next_student = 1;
	pthread_mutex_init(&station->lock,NULL);
	pthread_cond_init(&station->bus_arrive_cond,NULL);
	pthread_cond_init(&station->bus_loaded_cond,NULL);
}

void 
station_load_bus(struct station *station, int count)
{
	// Locking mutex
	pthread_mutex_lock(&station->lock);
	// Setting available seats to the count passed
	station->available_seats = count;
	// Notify the threads that the bus has arrived
	pthread_cond_broadcast(&station->bus_arrive_cond);
	// While theres students waiting and seats available, wait
	while(station->waiting_students > 0 && station->available_seats > 0){
		pthread_cond_signal(&station->bus_arrive_cond);
		pthread_cond_wait(&station->bus_loaded_cond, &station->lock);
	}
	// Reset seats for next bus
	station->available_seats = 0;
	// Unlocking mutex
	pthread_mutex_unlock(&station->lock);
}


int
station_wait_for_bus(struct station *station, int myticket, int myid)
{
	// Locking mutex

	// Increment the waiting students number

	// While the students ticket is not the next ticket

	// Decrement waiting students and available seats

	// Get the ticket of the next student

	// Increment next ticket and student number

	// Signal the bus is loaded

	// Unlocking mutex

	return my_board_order;
}
