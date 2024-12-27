from pymongo import MongoClient


class MongoDB(object):
    def __init__(self, host: str = 'localhost',
                 port: int = 27017,
                 db_name: str = None,
                 collection: str = None):
        self._client = MongoClient(f'mongodb://{host}:{port}')
        self._collection = self._client[db_name][collection]
        self._indexes = {}
    
    def add_array(self, array: list):
        try:
            self._collection.insert_one({"content": array})
            #self._indexes
        except Exception as error:
            print("Error in add_array:", error)
    
    def delete_array(self, index: int):
        try:
            _id = self._get_id(index) #change
            self._collection.delete_one({"_id": _id})
        except Exception as error:
            print("Error in delete_array:", error)
    
    def _get_id(self, index: int):
        if len(self._indexes) < self._collection.count_documents({}):
            self._indexes.clear()
            i = 1
            for doc in self._collection.find():
                self._indexes[i] = doc["_id"]
                i += 1
        return self._indexes[index]
    
    def get_array(self, index: int):
        try:
            return self._collection.find_one({"_id": self._get_id(index)})
        except Exception as error:
            print("Error in get_array:", error)

    def get_all_arrays(self):
        try:
            data = self._collection.find()
            return data
        except Exception as error:
            print("Error in get_all_arrays:", error)
    
    def replace_array(self, index: int, content):
        try:
            if self._collection.find_one({"_id": self._get_id(index)}) is not None:
                self._collection.update_one({"_id": self._get_id(index)}, {"$set": {"content": content}})
        except Exception as error:
            print("Error in replace_array:", error)
    
    def test_connection(self):
        try:
            self._collection.count_documents({})
            return True
        except Exception as error:
            print("Connection error:", error)
            return False


if __name__ == "__main__":
    database = MongoDB(db_name = "arrays", collection = "collection1")
    #database.add_array("10 2 42 3241")
    #database.add_array({"_id": 3, "content": [10, 320, 2124, 132132, 9]})
    #print(database._collection)
    #print(database.get_array(3))
    
    #for i in range(1, len(list(database.get_all_arrays())) + 1):
     #   database.delete_array(i)
    #x = database._collection.delete_many({})
    #print(x.deleted_count, len(list(database.get_all_arrays())))
    
    #print(list(database.get_all_arrays()))

