#define KEY 2004
#define BUF_SIZE 15

static struct sembuf set_free[1] = { 0, BUF_SIZE, 0 };

static struct sembuf wait_not_full[1] = { 0, -1, 0 };
static struct sembuf wait_not_empty[1] = { 1, -1, 0 };

static struct sembuf release_empty[1] = { 0, 1, 0 };
static struct sembuf release_full[1] = { 1, 1, 0 };

static struct sembuf mem_lock[1] = { 2, -1, 0 };
static struct sembuf mem_unlock[1] = { 2, 1, 0 };
