#ifndef OBJECT_H
#define OBJECT
template<class T>
class Node {
	T data;
	Node* next;
public:
	Node(T m_data) {
		data = m_data;
	}
	T getData() {
		return data;
	}
};
template<typename K>
void Insert(K a, Node <K>head) {

}
#endif // !OBJECT_H
