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
	// write your code here
}

int
station_wait_for_bus(struct station *station, int myticket, int myid)
{
	// write your code here
}
