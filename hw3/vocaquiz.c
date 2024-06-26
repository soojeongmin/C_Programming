#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list
{
	char eng[15];
	char kor[10];
	struct list *next;
};

typedef struct list ELEMENT;
typedef ELEMENT *LINK;
int correct, question;

void quiz(LINK head)
{
	float score;
	int enter;
	char ch, answer[15];
	if(head==NULL)
	{
		if(question==0) score = 0;
		else score = ((float)correct/question)*100;
		printf("당신의 점수는 %.2f 점입니다.\n", score);
		ch = getchar();
		while(1)
		{
			ch = fgetc(stdin);
			if(ch==0x0A)
			{
				system("clear");
				return;
			}
			ch = getchar();
		}
	}
	else 
	{
		printf("%s -> ", head->kor);
		scanf("%s", answer);
		if(strcmp(answer,".quit")==0)
		{
			if(question==0) score=0;
			else score = ((float)correct/question)*100;
			printf("당신의 점수는 %.2f 점입니다.", score);
			ch = getchar();
			while(1)
			{
				ch = fgetc(stdin);
				if(ch==0x0A)
				{
					system("clear");
					return;
				}
				ch = getchar();
			}
		}
		else
		{
			if(strcmp(answer, head->eng)==0)
			{
				correct++;
				printf("correct!\n");
			}
			else
			{
				printf("incorrect!\n");
			}
			question++;
			quiz(head->next);
		}
	}
}

int main(void)
{
	int choice, count=0;
	FILE *ofp;
	ELEMENT l;
	LINK head, temp, prev, p;

	ofp = fopen("dic.txt","r");
	while(1)
	{
		fscanf(ofp, "%s %s", l.eng, l.kor);
		if(feof(ofp)) break;
		count++;
	}
	fclose(ofp);

	ofp = fopen("dic.txt", "r");
	for(int i=0;i<count;i++)
	{
		fscanf(ofp, "%s %s", l.eng, l.kor);
		temp = malloc(sizeof(ELEMENT));
		
		strcpy(temp->eng, l.eng);
		strcpy(temp->kor, l.kor);
		temp->next = NULL;

		if(head==NULL) head = temp;
		else
		{
			if(strcmp(l.eng, head->eng)<0)
			{
				temp->next = head;
				head = temp;
			}
			else
			{
				p = head;
				while(p!=NULL&&(strcmp(l.eng, p->eng)>0))
				{
					prev = p;
					p = p->next;
				}
				temp->next = prev->next;
				prev->next = temp;
			}
		}
	}
	p = head;
	fclose(ofp);

	while(1)
	{
		printf(">> 영어 단어 맞추기 프로그램 <<\n");
		printf("1. 영어 단어 맞추기              2. 프로그램 종료\n\n");
		printf("번호를 선택하세요: ");
		scanf("%d", &choice);
	
		if(choice==1)
		{
			correct = 0;
			question = 0;
			system("clear");
			printf(">> 영어 단어 맞추기 <<\n");
			quiz(head);
		}
		else if(choice==2) 
		{
			system("clear");
			break;
		}
	}
	return 0;
}
