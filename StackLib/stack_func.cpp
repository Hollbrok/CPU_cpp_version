#include "stack.h"

static int ERROR_STATE_STACK = 0;
Stack::Stack(const char *name, size_t capacity) :
	canary_left_(static_cast<int> ( CANARY_L_STACK )),
	data_(nullptr),
	name_(name),
	capacity_(capacity),
	cur_size_(0),
	hash_(0),
	error_state_(0),
	canary_right_(static_cast<int> ( CANARY_L_STACK ))
{
	assert(this && "You passed nullptr to stack_consturct");

    data_ = (data_type*) calloc(capacity + 2, sizeof(data_type));
	assert(data_ && "Can't calloc memory for data_\n");

    data_[0] = static_cast<data_type> ( CANARY_LEFT_DATA );
    data_[capacity + 1] = static_cast<data_type> ( CANARY_RIGHT_DATA );

    for(int i = 1; i < capacity + 1; i++)
        data_[i] = POISON;

    data_++;

	//ASSERT_OK
}

Stack::~Stack()
{
	assert(this && "Stack is nullptr in ~Stack\n");
    //ASSERT_OK

    for(int i = -1; i <= capacity_; i++)
    	data_[i] = POISON;

    data_type* pointer =(data_type*) ((char*)data_ - sizeof(data_type));
    free(pointer);

    data_ = nullptr;

    cur_size_ = -1;
    capacity_ = -1;

}

void Stack::push (data_type push_num)
{
    assert((push_num != NAN) && "You passed incorrect number to push_stack");
    assert(this && "You passed nullptr to push");
    //ASSERT_OK

    FILE* res = fopen("log_stack.txt", "ab");
	assert(res && "cann't open log_stack.txt\n");

    if(cur_size_ == capacity_)
    {
        printf("Must call add_memory in push\n") ;//add_memory();
        data_[cur_size_++] = push_num;
        this->calc_hash(); // hash_stack(Stack);
    }
    else
    {
        data_[cur_size_++] = push_num;
        this->calc_hash(); // hash_stack(Stack);
    }
	fclose(res);
    return;
}

data_type Stack::pop()
{
	assert(this && "You passed nullptr to pop");
    // verify();

    // ASSERT_POP_OK

    if(false)//if(Stack->cur_size <= (Stack->capacity / REAL_MULTIPLIER + 1))
    {
        printf("Must call add_memory in pop\n") ;//add_memory();
        cur_size_--;
        data_type temp = data_[cur_size_];
        data_[cur_size_] = POISON;

		this->calc_hash(); // hash_stack(Stack);
        //ASSERT_POP_OK
        return temp;
    }

    else if(cur_size_ > 0)
    {
		cur_size_--;
        data_type temp = data_[cur_size_];
        data_[cur_size_] = POISON;

        this->calc_hash(); // hash_stack(Stack);
        //ASSERT_POP_OK
        return temp;
    }

    //ASSERT_POP_OK
	printf("cur_size <= 0 in pop\n");
    return  POISON;

}

void Stack::dump()
{
	assert(this && "You passed nullptr to dump");

    // char* sec_lvl = define_lvl();
    printf("In dump\n");
    char mass[67] = "******************************************************************";

    FILE* res = fopen("log_stack.txt", "ab");
    assert(res && "can't open file log_stack.txt");
    fprintf(res, "\n%*s\n", 66, mass);

	using namespace my_errors;

    if(error_state_)
    {
        printf("error_state_ = %d\n", error_state_);
		for(int i = 0; i < NUMBER_OF_ERRORS; i++)
			if(get_byte(error_state_, i + 1))
				fprintf(res, "Stack (ERROR #%d : %s) [%p]. \n",
				error_state_, error_print(i + 1), this);
    }
    else
    {
        fprintf(res, "Stack(OK) [%p]. \"%s\"\n", this, name_);

        // fprintf(res, "Security lvl is %s\n", sec_lvl);
        // fprintf(res, "Type of data is %s\n", type_string);
        fprintf(res, "Hash        = %d\n", hash_);
        fprintf(res, "size        = %Iu\n", cur_size_);
        fprintf(res, "capacity    = %Iu\n", capacity_);
        size_t cap = capacity_;
        size_t cur = cur_size_;

        for(int i = 0; i < cap; i++)
        {
            if(i < cur)
                fprintf(res, "*[%d] data   = %lg\n", i, data_[i]);
            else
                fprintf(res, "*[%d] data   = %lg (POISON)\n", i, POISON);
        }
    }


    fprintf(res, "%*s\n\n", 66, mass);
    fclose(res);

    return;
}

int Stack::verify()
{
    assert(this && "You passed nullptr to verify");
    int hash_st = hash_;

    using namespace my_errors;

    if(ERROR_STATE_STACK == MAX_CAPACITY_ERROR)
    {
		error_state_ += MAX_CAPACITY_ERROR;
        return MAX_CAPACITY_ERROR;
    }

    else if((this == nullptr))
    {
        error_state_ += NULL_STACK_PTR;
        return NULL_STACK_PTR;
    }

    else if(hash_st != this->calc_hash())
    {
        error_state_ += HACK_STACK;
        return HACK_STACK;
    }

    else if(data_ == nullptr)
    {
        error_state_ += NULL_DATA_PTR;
        return NULL_DATA_PTR;
    }

    else if(cur_size_ > capacity_)
    {
        error_state_ += CUR_BIGGER_CAPACITY;
        return CUR_BIGGER_CAPACITY;
    }

    else if(cur_size_ < 0)
    {
        error_state_ += CUR_LESS_ZERO;
        return CUR_LESS_ZERO;

    }
    else if(data_[-1] != CANARY_LEFT_DATA)
	{
        error_state_ += ERROR_DATA_LEFT;
        return ERROR_DATA_LEFT;
    }

    else if(data_[capacity_] != CANARY_RIGHT_DATA)
    {
        error_state_ += ERROR_DATA_RIGHT;
        return ERROR_DATA_RIGHT;
    }

    else if(canary_left_ != static_cast<int> ( CANARY_L_STACK) )
    {
        error_state_ += ERROR_STACK_LEFT;
        return ERROR_STACK_LEFT;
    }

    else if(canary_right_ != static_cast<int> ( CANARY_R_STACK ) )
    {
        error_state_ += ERROR_STACK_RIGHT;
        return ERROR_STACK_RIGHT;
    }

    else
    {
        printf("No errors in verify\n");
        return false;
    }
}

char* Stack::error_print(int bit_of_error)
{
    char error_message[100] = {};
    switch(bit_of_error)
    {
        case 1:
            strcpy(error_message, "NULL STACK PTR"); //error_message = "NULL STACK PTR";
            break;
        case 2:
            strcpy(error_message, "NULL DATA PTR");
            break;
        case 3:
            strcpy(error_message, "CUR BIGGER THAN CAPACITY");
            break;
        case 4:
            strcpy(error_message, "CUR LESS THAN ZERO");
            break;
        case 5:
            strcpy(error_message, "CAPACITY LESS THAN ZERO");
            break;
        case 6:
            strcpy(error_message, "DOUBLE CONSTRUCT");
            break;
        case 7:
            strcpy(error_message, "ERROR_DATA_LEFT");
            break;
        case 8:
            strcpy(error_message, "ERROR_DATA_RIGHT");
            break;
		case 9:
            strcpy(error_message, "Somebody is trying to hack a stack");
            break;
        case 10:
            strcpy(error_message, "MAX_CAPACITY_ERROR");
            break;
        default:
            strcpy(error_message, "UNKNOWN ERROR IN error_print()\n");
            break;

    }
    return error_message;
}

int Stack::calc_hash()
{
	assert(this && "You passed nullptr to hash_stack\n");

    /*int cur_size = 0;
    for(int i = 0; i < Stack->capacity; i++)
        if(Stack->data[i] != POISON)
        {
            printf("Stack->data[%d] = %lg\n", i, Stack->data[i]);
            cur_size++;
        }
    printf("cur_size = %d\n", cur_size);*/

    if(cur_size_ == 0)
    {
        hash_ = 0;
        return 0;
    }

    int Hash = 1;
    int N    = capacity_;
    double A = (sqrt(5) - 1) / 2;


    //double trash = 0;

    for(int i = 0; i < cur_size_; i++)
    {
        Hash += (int) (N * ((double)(A * ((int) (data_[i]) | (int) (data_[i - 1]))) - (int) (A * ((int) (data_[i]) | (int) (data_[i - 1]))))) + (int) (data_[i]) ^ (int)
        (data_[i - 1]) - ((int) (data_[i]) & (int) (data_[i - 1]));
        Hash += capacity_;
        //Hash += ((int)(Stack->data));
        Hash += *(name_ + strlen(name_) % 2);//>> i % 2;
    }

    Hash += abs((canary_left_ >> 2));
    Hash += (capacity_ * canary_right_) >> 2;

    hash_ = Hash;
    return Hash;
}

auto get_byte(int digit, int number_of_bit) -> bool
{
    return (bool((1 << (number_of_bit - 1))  &  digit));
}
