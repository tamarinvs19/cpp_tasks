#pragma once

#include <cstddef>
#include <climits>
#include <optional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <exception>
#include <cmath>

namespace lab_17 {
    /**
     * Exception thrown when queue is shut down.
     * Any operation that was waiting inside the queue or would modify it after shutdown is aborted with this exception.
     */
    class queue_is_shutdown: public std::logic_error {
	public:
	    queue_is_shutdown() : std::logic_error("Error! Queue is shutdown") {}
    };

    /**
     * Synchronised queue for inter.
     * @tparam T stored type.
     */
    template<typename T>
    class sync_queue {
    public:
        /**
         * Construct queue with given maximum queue size (unlimited by default).
         * @param max_size maximum queue size.
         */
        explicit sync_queue(std::size_t max_size = UINT_MAX) : max_size(max_size) {}
        /**
         * Move construction.
         */
        sync_queue(sync_queue &&) noexcept;
        /**
         * Move assignment.
         */
        sync_queue &operator =(sync_queue &&) noexcept;
        /**
         * Destruction.
         */
        ~sync_queue() noexcept {
	    if (!is_shutdown())
		shutdown();
	}

        /**
         * Copy construction is forbidden.
         */
        sync_queue(sync_queue const &) = delete;
        /**
         * Copy assignment is forbidden.
         */
        sync_queue &operator =(sync_queue const &) = delete;

        /**
         * Push value into the queue, wait if needed.
         * If queue was already shutdown or is shutdown during waiting, exception is thrown.
         * @param value value to be pushed (todo: references?)
         */
        void push(T value) {
	    std::unique_lock<std::mutex> lock(m_q);
	    if (s_q.size() < max_size) 
		full.wait(lock, [this](){return !working || s_q.size() < max_size;});
	    if (!working)
		throw queue_is_shutdown();
	    do_try_push(value);
	}
        /**
         * Push value into the queue only if there is space for it.
         * If queue was shutdown, operation is not performed.
         * @param x value to be pushed (todo: references?)
         * @return was operation successful or not.
         */
        bool try_push(T value) {
	    std::unique_lock<std::mutex> lock(m_q);
	    if (!working)
		return false;
	    return do_try_push(value);
	}

        /**
         * Pop value from the queue, wait if needed.
         * If queue was already shutdown or is shutdown during waiting, exception is thrown.
         * @return popped value.
         */
        T pop() {
	    std::unique_lock<std::mutex> lock(m_q);
	    if (s_q.size() == 0) 
		full.wait(lock, [this](){return !working || s_q.size() == 0;});
	    if (!working)
		throw queue_is_shutdown();
	    return do_try_pop();
	}
        /**
         * Pop value from the queue only if there is one.
         * If queue was shutdown, operation is not performed
         * @return optional popped value.
         */
        std::optional<T> try_pop() {
	    std::unique_lock<std::mutex> lock(m_q);
	    if (!working)
		return false;
	    return do_try_pop();
	}

        /**
         * Current size of queue.
         * @return size.
         */
        std::size_t size() const noexcept {
	    std::unique_lock<std::mutex> lock(m_q);
	    return s_q.size();
	}

        /**
         * Shutdown queue.
         * After queue is shutdown, nothing can be pushed or popped,
         * and all waiting operations are aborted.
         */
        void shutdown() noexcept {
	    std::unique_lock<std::mutex> lock(m_q);
	    working = false;
	    empty.notify_all();
	    full.notify_all();
	}
        /**
         * Check if queue is shutdown.
         * @return is queue shutdown.
         */
        bool is_shutdown() const noexcept {
	    return working;
	}

    private:
        /*
         * Implementation is left out.
         */
	std::queue<T> s_q;
	std::mutex m_q;
	std::size_t max_size;

	bool working = true;

	std::condition_variable full, empty;

	bool do_try_push(T value) {
	    if (s_q.size() == max_size)
		return false;
	    s_q.push(value);
	    empty.notify_one();
	    return true;
	}

	std::optional<T> do_try_pop() {
	    if (s_q.size() == 0)
		return std::nullopt;
	    T value = s_q.pop();
	    full.notify_one();
	    return value;
	}
    };

    class worker {
    public:
	worker() {}

	std::vector<int> search_primes(int left, int right) {
	    std::vector<int> res;
	    for (int num = left; num < right; ++num) {
		if (check_prime(num))
		    res.push_back(num);
	    }
	    return res;
	}

	bool check_prime(int num) {
	    for (int i = 0; i <= sqrt(num); ++i) {
		if (num % i == 0)
		    return false;
	    }
	    return true;
	}
    };
}
