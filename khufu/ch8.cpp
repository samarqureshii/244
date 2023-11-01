class ListNode {
 public:
  int key;
  ListNode* next;
};
ListNode* head;

void removeNode(ListNode* node){
    ListNode* next = node->next;
    node->key = next->key;
    node->next = next->next;
    delete next;
}

























A::A(string text, int barray_max_size){
    s = text;
    barray = new B*[barray_max_size];
    for(int i = 0; i<barray_max_size; i++){
        barray[i] = NULL;
    }
}