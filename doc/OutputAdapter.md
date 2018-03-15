# APIAdapter

- 人员：李嘉恒、黄晓琳
- 目标：实现UDP、TCP通信和文件读写

## OutputAdapter

- 基本框架

  ```c++
  class OutputAdapter	//父类
  	OutputAdapter(){};
  	~OutputAdapter(){};
  	virtual void init();	// 纯虚函数，初始化连接
  	virtual void send(Frame dataframe);	// 纯虚函数，发送数据
  	virtual void Close();	// 纯虚函数，关闭连接

  class UdpOutputAdapter : public OutputAdapter	//UDP接口
  	UdpOutputAdapter(int, char[]);	// 构造函数，初始化端口、IP
  	void init();	// 初始化UDP连接
  	void send(Frame dataframe);	// 发送数据
  	void Close();	//关闭UDP连接

  class TcpOutputAdapter : public OutputAdapter	//TCP接口
  	TcpOutputAdapter(int, char[]);	//构造函数，初始化端口、IP
  	void init();	// 初始化TCP连接
  	void send(Frame dataframe);	//发送数据
  	void Close();	//关闭TCP连接
  ```



- 使用演示

  ```c++
  OutputAdapter *opa = new UdpOutputAdapter(8888, addr);
  Frame frame;
  opa->init();
  opa->send(frame);
  opa->Close();
  ```



## InputAdapter

- 基本框架

  ```c++
  class InputAdapter:
  	InputAdapter(){};
  	~InputAdapter(){};
  	virtual void init();	// 纯虚函数，初始化连接
  	virtual void receive(Frame &frame);	// 纯虚函数，接收数据
  	virtual void Close();	// 纯虚函数，关闭连接

  class UdpInput : public InputAdapter	// UDP接口
  	UdpInput(int, char*);	//构造函数，初始化端口和IP
  	~UdpInput(){};
  	void init();	// 初始化连接
  	void receive(Frame &frame);	// 接收数据
  	void Close();	// 关闭UDP连接

  class TcpInput : public InputAdapter	// TCP接口
      TcpInput(int, char*)	// 构造函数，初始化端口和IP
      ~TcpInput(){};
  	void init();	// 初始化TCP连接
  	void receive(Frame &frame);	// 接收数据
  	void Close();	//关闭TCP连接
  ```

  ​

- 使用演示

  ```
  OutputAdapter *opa = new TcpOutputAdapter(8888, addr);
  Frame frame;
  opa->init();
  opa->send(frame);
  opa->Close();
  ```

  ​