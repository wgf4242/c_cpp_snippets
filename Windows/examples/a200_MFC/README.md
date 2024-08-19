

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