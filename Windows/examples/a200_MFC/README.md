

启动窗口

```c
MineDlg* Dlg;
Dlg = new MineDlg();
Dlg->DoModal();
```

关闭窗口
```c
void CMyDialog::OnClose() 
{
    DestroyWindow();
}
```

## 常用 



```
AfxMessageBox(L"MessageBox"); // 消息框
```



## Edit文本内容



```
	//method 1
	{
		CString value;
		GetDlgItem(IDC_EDIT1)->GetWindowText(value);
		CString newValue("hello");
		GetDlgItem(IDC_EDIT1)->SetWindowText(newValue);
	}

	//method 2
	{
		CString value;
		GetDlgItemText(IDC_EDIT1, value);
		CString newValue("hello");
		SetDlgItemText(IDC_EDIT1, newValue);

		//we can use GetDlgItemInt/SetDlgItemInt when content is int value
	}

	//method 3
	{
		//connect variable and corresponding control

		//step1, add below line in DoDataExchange
		DDX_Control(pDX, IDC_EDIT1, m_edit1);

		//step2
		CString value;
		m_edit1.GetWindowText(value);
		CString newValue("hello");
		m_edit1.SetWindowText(newValue);
	}

	//method 4, through window message
	{
		char value[512];
		m_edit1.SendMessage(WM_GETTEXT, 512, (LPARAM)value);
		char newvalue[512];
		m_edit1.SendMessage(WM_SETTEXT, 512, (LPARAM)newvalue);
	}

	//method 5, through dialog message
	{
		char value[512];
		SendDlgItemMessage(IDC_EDIT1, WM_GETTEXT, 512, (LPARAM)value);
		char newvalue[512];
		SendDlgItemMessage(IDC_EDIT1, WM_SETTEXT, 512, (LPARAM)newvalue);
	}
```

