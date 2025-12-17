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
	pthread_mutex_lock(&station->lock);
	station->available_seats = count;

	/* Wake up waiting students (if any) so they can board. */
	if (station->available_seats > 0)
		pthread_cond_broadcast(&station->bus_arrive_cond);

	/* Wait until bus is full or no more waiting students. */
	while (station->available_seats > 0 && station->waiting_students > 0) {
		pthread_cond_wait(&station->bus_loaded_cond, &station->lock);
		/* After a student boarded, wake up next waiting student (if any and seats left). */
		if (station->available_seats > 0 && station->waiting_students > 0)
			pthread_cond_broadcast(&station->bus_arrive_cond);
	}

	/* Bus leaves: set available seats to zero. */
	station->available_seats = 0;
	pthread_mutex_unlock(&station->lock);
}

int
station_wait_for_bus(struct station *station, int myticket, int myid)
{
	pthread_mutex_lock(&station->lock);
	station->waiting_students++;

	/* Wait until a bus with free seats is present AND it's this student's turn. */
	/* TODO update here:
	 * Wait until:
	 *  - a seat is available, AND
	 *  - either it's this student's ticket turn, OR the student is VIP (id == 5).
	 */
	while (myticket != station->next_student || station->available_seats == 0) {
		pthread_cond_wait(&station->bus_arrive_cond, &station->lock);
	}

	/* Board the bus */
	station->waiting_students--;
	station->available_seats--;
	int myturn = station->next_ticket;
	station->next_ticket++;
	station->next_student++;

	/* Notify the bus that a student has boarded */
	pthread_cond_signal(&station->bus_loaded_cond);

	pthread_mutex_unlock(&station->lock);
	return myturn;
}
