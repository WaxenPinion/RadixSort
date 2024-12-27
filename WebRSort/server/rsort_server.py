from http.server import SimpleHTTPRequestHandler, HTTPServer
from Mongodb import MongoDB


class MyHandler(SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        self.database = MongoDB(db_name = "arrays", collection = "collection1")
        #print("Соединение с базой данных: ", self.database.test_connection())
        super().__init__(*args, **kwargs)
    
    def do_GET(self):
        
        #self.send_response(200)
        #self.send_header('Content-type', 'text/html')
        #self.end_headers()
        if not self.database.test_connection():
            self._start_response(500)
            return
        
        if self.path == "/?all":
            self._start_response(200)
            content = ""
            
            for array in self.database.get_all_arrays():
                content += array["content"] + "/"
            
            self.wfile.write(content.encode('utf-8'))
            return
        
        index = 0
        try:
            index = int(self.path[8:])
        except Exception as error:
            print(error)
            
            self._start_response(400)
            return
        
        array = self.database.get_array(index)
        
        if (array != None):
            self._start_response(200)
            self.wfile.write(str(array["content"]).encode('utf-8'))
        else:
            self._start_response(204)
        
    def do_POST(self):
        
        if not self.database.test_connection():
            self._start_response(500)
            return
        
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length)
        
        parts = post_data.decode('utf-8').split("/")
        
        if parts[0] == "add" and len(parts) == 2:
            self.database.add_array(parts[1])
            self._start_response(200)
            
        elif parts[0] == "change" and len(parts) == 3:
            try:
                index = int(parts[1])
                self.database.replace_array(index, parts[2])
                self._start_response(200)
                
            except Exception as error:
                print(error)
                self._start_response(400)
        elif parts[0] == "delete" and len(parts) == 2:
            try:
                index = int(parts[1])
                
                if self.database.get_array(index) == None:
                    self._start_response(204)
                    return
                
                self.database.delete_array(index)
                self._start_response(200)
            except Exception as error:
                print(error)
                self._start_response(400)
        else:
            self._start_response(400)
    
    def _start_response(self, status_code):
        self.send_response(status_code)
        self.send_header('Content-type', 'text/html')
        self.end_headers()


while True:
    server_address = list(input("Введите адрес сервера: ").split())

    if len(server_address) == 0:
        server_address = ('localhost', 8000)
        break
    elif len(server_address) == 2:
        server_address[1] = int(server_address[1])
        break
    else:
        print("Некорректный адрес")
    
httpd = HTTPServer(tuple(server_address), MyHandler)

print(f"Запуск сервера по адресу {server_address[0]}:{server_address[1]}")
httpd.serve_forever()
