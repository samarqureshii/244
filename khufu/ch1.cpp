//Question 6 in Fall 2022 Midterm Exam [Easy]:

void swap_by_p(int* a, int* b) { //swapping by pointer
    int temp = *a;
    *a = *b;
    *b = temp;

}
void swap_by_r(int& a, int& b) { //swapping by reference
    int temp = a;
    a = b;
    b = temp;

}

int main(){
    int x = 1, y = 0;
    swap_by_p(&x, &y);
    return 0;

}




