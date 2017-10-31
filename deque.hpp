#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"
#include <cstddef>
#include <iostream>
#include <cstdio>

using namespace sjtu;

namespace sjtu {
	template<class T>

	class deque {

	public:
		struct fnode {
			fnode * pre;
			fnode * next;
			fnode() :pre(NULL), next(NULL) {}
			fnode(const fnode& other){
                pre = other.pre;
                next = other.next;
			}
			virtual ~fnode() {}
		};

		struct node :public fnode {
			T elem;
            node(const T&x):elem(x){}
			~node() {
			}
		};

		class const_iterator;

		class iterator {

		private:
			fnode * p;

		public:
			iterator() {
				p = new fnode();
			}

			iterator(const T &x)
			{
				node *q = new node(x);
				p = q;
				q = NULL;
			}

			~iterator() {}

			void clear() {
				if (p != NULL) {
					delete p;
				}
				p = NULL;
			}

			iterator operator+(const int &n) const {
				if (n<0) {
					int x = -n;
                    iterator tmp = *this;

					while (x--)
					{
						tmp--;
					}

					return tmp;
				}

				int x = n;
				iterator tmp = *this;

				while (x--)
				{
					tmp++;
				}

				return tmp;
			}

			iterator operator-(const int &n) const {
				if (n<0) {
					int x = -n;
					iterator tmp = *this;

					while (x--)
					{
						tmp++;
					}

					return tmp;
				}

				int x = n;
				iterator tmp = *this;

				while (x--)
				{
					tmp--;
				}

				return tmp;
			}

			int operator-(const iterator &rhs) const {
				if (*this == rhs) return 0;

				iterator tmp = *this;
				int x = 0;

				while (!tmp.is_head())
				{
					tmp--;
					x++;
                    if (tmp == rhs) {
						return x;
					}
				}
				x = 0;
                tmp = *this;
				while (!tmp.is_end())
				{
					tmp++;
					x--;
					if (tmp == rhs) {
						return x;
					}
				}

				throw invalid_iterator();
			}

			bool is_head() {
				return p->pre == NULL;
			}

			bool is_end() {
				return p->next == NULL;
			}

			iterator operator+=(const int &n) {
				if (n<0) {
					int x = -n;

                    while (x--)
                    {
                        if (p->pre == NULL) throw index_out_of_bound();
                        else p = p->pre;
                    }

                    return *this;
				}
				int x = n;

                while (x--)
                {
                    if (p->next == NULL) throw index_out_of_bound();

                    else p = p->next;
                }

                return *this;
			}

			iterator operator-=(const int &n) {

				if (n<0) {

					int x = -n;

                    while (x--)
                    {
                        if (p->next == NULL) throw index_out_of_bound();

                        else p = p->next;
                    }

                    return *this;
				}

				int x = n;

                while (x--)
                {
                    if (p->pre == NULL) throw index_out_of_bound();

                    else p = p->pre;
                }
					return *this;
			}

			iterator operator++(int) {

				iterator tmp = *this;

                if (p->next == NULL) throw index_out_of_bound();

                p = p->next;

                return tmp;
			}



			iterator& operator++() {
                if (p->next == NULL) throw index_out_of_bound();

                p = p->next;

                return *this;
			}

			iterator operator--(int) {
				iterator tmp = *this;

                if (p->pre == NULL) throw index_out_of_bound();

                p = p->pre;

                return tmp;
			}

			iterator& operator--() {
                if (p->pre == NULL) throw index_out_of_bound();

                p = p->pre;

                return *this;
			}

			T& operator*() const {
                if (p->next == NULL || p->pre == NULL) throw invalid_iterator();
				return (((node*)p)->elem);
			}


			T* operator->() const {
				return &(((node*)p)->elem);

			}

			bool operator==(const iterator &rhs) const {
				return operator->() == rhs.operator->();

			}

			bool operator==(const const_iterator &rhs) const {

				return operator->() == rhs.operator->();

			}

			bool operator!=(const iterator &rhs) const {

				return operator->() != rhs.operator->();

			}

			bool operator!=(const const_iterator &rhs) const {

				return operator->() != rhs.operator->();

			}

			fnode& return_node() const
			{

                if (p == NULL) throw invalid_iterator();

                return *p;
			}

		};

		class const_iterator {

		private:

			fnode * p;

		public:

			const_iterator() {

				p = new fnode();

			}

			const_iterator(T &x) {

				node *q = new node(x);
				p = q;
				q = NULL;
			}

			const_iterator(const const_iterator &other) {

				p = &other.return_node();
			}

			const_iterator(const iterator &other) {

				p = &other.return_node();
			}

			T& operator*() const {
                if (p->next == NULL || p->pre == NULL) throw invalid_iterator();
				return (((node*)p)->elem);

			}

			T* operator->() const {
				return &(((node*)p)->elem);
			}

			const_iterator operator+(const int &n) const {
				if (n<0) {
					int x = -n;
					const_iterator tmp = *this;

					while (x--)
					{
						tmp--;
					}

					return tmp;
				}

				int x = n;
				const_iterator tmp = *this;

				while (x--)
				{
                    tmp++;
				}

				return tmp;
			}

			const_iterator operator-(const int &n) const {

				if (n<0) {

					int x = -n;

					const_iterator tmp = *this;

					while (x--)
					{
						tmp++;
					}
					return tmp;
				}

				int x = n;

				const_iterator tmp = *this;

				while (x--)

				{

					tmp--;

				}

				return tmp;

			}

			int operator-(const const_iterator &rhs) const {

				if (*this == rhs) return 0;

				const_iterator tmp = *this;

				int x = 0;

				while (!tmp.is_head())
				{
					tmp--;
					x++;
					if (tmp == rhs) {
						return x;
					}
				}
				x = 0;
                tmp = *this;
				while (!tmp.is_end())
				{
					tmp++;
					x--;
					if (tmp == rhs) {
						return x;
					}
				}

				throw invalid_iterator();
            }

			bool is_head() {
				return p->pre == NULL;
			}

			bool is_end() {
				return p->next == NULL;
			}

			const_iterator operator+=(const int &n) {
				if (n<0) {

					int x = -n;

                    while (x--)
                    {
                        if (p->pre == NULL) throw index_out_of_bound();

                        else p = p->pre;
                    }

                    return *this;
				}

				int x = n;

                while (x--)
                {
                    if (p->next == NULL) throw index_out_of_bound();

                    else p = p->next;
                }

                return *this;
			}

			const_iterator operator-=(const int &n) {
				if (n<0) {
					int x = -n;

                    while (x--)
                    {
                        if (p->next == NULL) throw index_out_of_bound();

                        else p = p->next;

                    }

                    return *this;
				}

				int x = n;

                while (x--)
                {
                    if (p->pre == NULL) throw index_out_of_bound();

                    else p = p->pre;
                }

                return *this;
			}

			const_iterator operator++(int) {

				const_iterator tmp = *this;

                if (p->next == NULL) throw index_out_of_bound();

                p = p->next;

                return tmp;
			}

			const_iterator& operator++() {
                if (p->next == NULL) throw index_out_of_bound();

                p = p->next;

                return *this;
			}

			const_iterator operator--(int) {
				const_iterator tmp = *this;

                if (p->pre == NULL) throw index_out_of_bound();

                p = p->pre;

                return tmp;
			}

            const_iterator& operator--() {
                if (p->pre == NULL) throw index_out_of_bound();

                p = p->pre;

                return *this;
			}

			bool operator==(const iterator &rhs) const {

				return operator->() == rhs.operator->();

			}

			bool operator==(const const_iterator &rhs) const {

				return operator->() == rhs.operator->();

			}

			bool operator!=(const iterator &rhs) const {

				return operator->() != rhs.operator->();

			}

			bool operator!=(const const_iterator &rhs) const {

				return operator->() != rhs.operator->();

			}

			fnode& return_node() const

			{
                if (p == NULL) throw invalid_iterator();

                return *p;
			}
		};

	private:
		iterator head;
		iterator tail;
		size_t len;

	public:
		deque() {
			head.return_node().next = &tail.return_node();
			head.return_node().pre = NULL;
			tail.return_node().pre = &head.return_node();
			tail.return_node().next = NULL;
			len = 0;
		}

		deque(const deque &other) {
			head.return_node().next = &tail.return_node();
			tail.return_node().pre = &head.return_node();
			len = 0;

			if (!other.empty()) {
				int i = 0;
				while (other.begin() + i != other.end()) {
                    insert(tail, *(other.begin() + i));
					i++;
				}
			}
		}

		~deque() {
			clear();
		}

		deque &operator=(const deque &other) {
			if (this == &other) return *this;

			if (!empty()) clear();

			if (!other.empty()) {
				int i = 0;

				while (other.begin() + i != other.end()) {
					insert(tail, *(other.begin() + i));
					i++;
				}
			}

			return *this;
		}

		T & at(const size_t &pos) {
            if (empty() || pos >= len || pos<0) throw index_out_of_bound();

            else return *(head + (1 + pos));
		}

		const T & at(const size_t &pos) const {
            if (empty() || pos >= len || pos <0) throw index_out_of_bound();

            else return *(head + (1 + pos));
		}

		T & operator[](const size_t &pos) {
            if (empty() || pos >= len || pos<0) throw index_out_of_bound();

            else return *(head + (1 + pos));
		}

		const T & operator[](const size_t &pos) const {
            if (empty() || pos >= len || pos<0) throw index_out_of_bound();

            return *(head + (1 + pos));
		}

		const T & front() const {
			if (empty()) throw container_is_empty();
			else return *(head + 1);
		}

		const T & back() const {
			if (empty()) throw container_is_empty();
			else return *(tail - 1);
		}

		iterator begin() const {
			return (head + 1);
		}

		const_iterator cbegin() const {
			const_iterator tmp(head+1);
			return tmp;
		}

		iterator end() const {
			return tail;
		}

		const_iterator cend() const {
			const_iterator tmp(tail);
			return tmp;
		}

		bool empty() const {
			return len == 0;
		}

		size_t size() const {
			return len;
		}

		void clear() {

			iterator tmp = head+1;
			while (tmp != tail){
                tmp++;
                (tmp-1).clear();
			}
			head.return_node().next = &tail.return_node();
			tail.return_node().pre = &head.return_node();
			len = 0;

		}

		iterator insert(iterator pos, const T &value) {
			//int x = head - pos;
			iterator tmp(value);

			if (pos != tail) int x = pos - head;

			tmp.return_node().next = &(pos.return_node());
			tmp.return_node().pre = &((pos - 1).return_node());
			(pos - 1).return_node().next = &(tmp.return_node());
			pos.return_node().pre = &(tmp.return_node());

			len++;

			return tmp;
		}

		iterator erase(iterator pos) {

			if (empty()) throw container_is_empty();

			if (pos == head || pos == tail) throw invalid_iterator();

			if (pos != tail-1) int x = pos - head;

			(pos - 1).return_node().next = &(pos + 1).return_node();

			(pos + 1).return_node().pre = &(pos - 1).return_node();
			iterator tmp = pos+1;
            pos.clear();

			len--;

			return tmp;;

		}

		void push_back(const T &value) {

			insert(tail, value);

		}

		void pop_back() {
			if (empty()) throw container_is_empty();

			erase(tail - 1);
		}

		void push_front(const T &value) {
			insert(head + 1, value);
		}

		void pop_front() {
			if (empty()) throw container_is_empty();

			erase(head + 1);
		}
	};

}

#endif
