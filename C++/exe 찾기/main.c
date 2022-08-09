#include <windows.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

HWND hwnd_edit1, hwnd_listbox1;
HWND hwnd_button1, hwnd_button2;

void scan_dir(char *path){
	DIR *d;
	struct dirent* ent;
	struct stat st;
	char buf[256];
	char *r;
	
	printf("*** OPEN %s\n", path);
	
	d = opendir(path);
	while( (ent = readdir(d)) != NULL){
		
		// 만약에, ent->d_name이, "." 이거나, ".." 이면, "skip" 출력. strcmp 이용. 
		if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name, "..")==0)
			continue;
			
		sprintf(buf, "%s/%s", path, ent->d_name); 
		stat(buf, &st);
		if(S_ISDIR(st.st_mode)){  // 디렉터리
			scan_dir(buf);  // 새로운 경로. 기존 경로 + 디렉터리 이름. 
		}else if(S_ISREG(st.st_mode)){  // 일반 파일 
			printf("%s", ent->d_name); 
			// 파일끝 확장자가 ".exe" 파일의 끝에 "<<-- " 표시
			r = strrchr(ent->d_name, '.');
			if((r!=NULL) && (strcmp(r+1, "exe")==0)){
					//printf("<<--");
					SendMessage(hwnd_listbox1, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)buf);
					// remove(buf);
			}
		}
		printf("\n");
	}
	closedir(d);
}



/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		case WM_CREATE:{
			//MessageBox(hwnd, "Window CREATE!","WM_CREATE!",MB_ICONEXCLAMATION|MB_OK);
			
			hwnd_edit1 = CreateWindow("EDIT","", WS_VISIBLE|WS_CHILD|WS_BORDER, 5,5,90,25,hwnd,NULL,
				(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);	
				
			hwnd_button1 = CreateWindow("BUTTON","검색", WS_VISIBLE|WS_CHILD, 100,5,90,25,hwnd,NULL,
				(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
				
			hwnd_button2 = CreateWindow("BUTTON","삭제", WS_VISIBLE|WS_CHILD, 100,40,90,25,hwnd,NULL,
				(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
				
			hwnd_listbox1 = CreateWindow("LISTBOX","", WS_VISIBLE|WS_CHILD|WS_BORDER, 5,40,90,150,hwnd,NULL,
				(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
			
		
			break;
		}
		
		case WM_COMMAND:{
			WORD h_word, l_word;
			HWND hwnd_caller;
			char edit_buffer[100];
			
			h_word = HIWORD(wParam);
			l_word = LOWORD(wParam);
			
			hwnd_caller = (HWND)lParam;
			
			if(h_word == BN_CLICKED){
				
				if(hwnd_caller == hwnd_button1){
					//SendMessage(___메시지 받는 윈도우 핸들__, __메시지__,__응답값__)
					//SendMessage(hwnd_edit1, WM_GETTEXT, (WPARAM)100, (LPARAM)edit_buffer);
					//SendMessage(hwnd_listbox1, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)edit_buffer);
					//MessageBox(hwnd, edit_buffer,"Clicked",MB_ICONEXCLAMATION|MB_OK);
					
					//1. edit1에서 확장자 문자열 가지고 오기
					//2. scan_dir 함수를 고쳐서 새로 가져와 쓰기.
					//   - 지정된 확장자 사용
					//   - 파일 발견시 listbox1에 경로 추가 
					scan_dir(".");
	
					MessageBox(hwnd, "button1","Clicked",MB_ICONEXCLAMATION|MB_OK);
				}
					
				if(hwnd_caller == hwnd_button2)
					MessageBox(hwnd, "button2","Clicked",MB_ICONEXCLAMATION|MB_OK);
				
			}
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
