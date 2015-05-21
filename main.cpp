#include <string> // std::string
#include <fstream> // std::ifstream
#include <algorithm> // std::replace
#include <curl/curl.h> // curl stuff

/*

required library: json encoder & decoder

*/

typedef std::string string;

/*
  This Zermelo API class was developed by JulianvDoorn, 2015
  This project does not have any connections/is related to Zermelo itself!
 
  It contains all methods you can use to easily start your own app development
*/
class ZermeloAPI {
	/*
	  The school to use by the API
	*/
	
	protected:
		string school;
		
	/*
	  Using HTTPS or not
	*/
	
	private:
		bool secure;
	
	/*
	  Construct a new Zermelo instance, by any given school
	*/
	
	public:
		void ZermeloAPI(string& school, bool secure = false) {
			this->setSchool();
			this->secure = secure;
		}
		
		string* getStudentGridAhead(string& id, int weeks = 1) {
			int start, end;
			if (weeks == 1) {
				start = strtotime('monday this week midnight'); //////////////////////////////////////////
				end = strtotime('saturday this week'); //////////////////////////////////////////
			} else {
				if (weeks == 2) {
					start = strtotime('next week monday midnight'); //////////////////////////////////////////
					end = strtotime('next week saturday'); //////////////////////////////////////////
				} else {
					start = strtotime('+' . $weeks . ' weeks monday midnight'); //////////////////////////////////////////
					end = strtotime('+' . $weeks . ' weeks saturday'); //////////////////////////////////////////
				}
		}
		return this->getStudentGrid(id, start, end);
		}
		
		string* getStudentGrid(string& id, int start = NULL, int end = NULL) {
			if (start) start = strtotime('last monday', strtotime('tomorrow')); /////////////////////////
			if (end) end = strtotime('last saturday', strtotime('tomorrow')); ///////////////////////////// notice me senpai
			string token = this->getToken($id);
			string raw = this->callApi("api/v2/appointments", array('access_token' => $token, 'start' => $start, 'end' => $end, 'user' => '~me')); ///////////////////////// omgf
			json = json_decode(raw, true)['response'];
			if (this->validateData($json))
			{
				string* grid = this->optimizeGrid($json['data']);
				return grid;
			}
			return new string[0];
		}
		
		string* getAnnouncementsAhead(string& id, int weeks = 1) {
			int start, end;
			if (weeks == 1) {
				start = strtotime('next monday'); ////////////// 2 much
				end = strtotime('next saturday'); ///////////
			} else {
				start = strtotime('+' . $weeks . ' weeks monday'); ////////////
				end = strtotime('+' . $weeks . ' weeks saturday'); ///////////
			}
			return this->getAnnouncements(id, start, end);
		}
		
		string* getAnnouncements(string& id, int start = NULL, int end = NULL) {
			// Set the start times if they are not set
			if (start) start = strtotime('last monday', strtotime('tomorrow')); ///////////////////////////////////////////////////////////// *error*
			if (end) end = strtotime('last saturday', strtotime('tomorrow')); ////////////////////////////////////////
			string token = this->getToken(id);
			string raw = this->callApi("api/v2/announcements", array('access_token' => $token, 'start' => $start, 'end' => $end)); ////////////////////////////////////////////////////////// solve this
			json = json_decode($raw, true)['response'];
			if ($this->validateData(json)) {
				return json['data'];
			}
			return new string[0];
		}
		
		string* grabAccessToken(string& user, string code, bool save = true) {
			std::replace(code.begin(), code.end(), " ", "");
			string raw = this->callApiPost("api/v2/oauth/token", array('grant_type' => 'authorization_code', 'code' => $code)); ///////////////////////////////////////////// solve this
			try {
				if (raw.find("Error report") == std::string::npos)  {
					throw "Couldn't grab access token, did you double check the code from the portal?";
				}
				string* json = json_decode($raw, true);
				if (save) this->saveToken(user, json['access_token']); ////////////////////////////////////////////////////////////////////////////////////////////////////// and this
				return string* json;
			} catch (string& str) {
				std::cout << str << std::endl;
			}
		}
		
		bool invalidateAccessToken(string& id) {
			string token = this->getToken(id);
			string raw = this->callApiPost("/api/v2/oauth/logout", array('access_token' => $token)); ////////////////////////////////////////////////////////////// also this
			if (raw.length() == 0) {
				return true;
			}
			return false;
		}
		
		void setSchool(string school) {
			this->school = school;
		}
		
		string getToken(string& id) {
			std::ifstream cache("cache.json", ios::in | ios::binary | ios::ate);
			if (cache) {
				size = cache.tellg();
				string content = new char [size];
				cache.seekg(0, ios::beg);
				cache.read(content, size);
				cache.close();
				json = json_decode(content, true);
				return json.tokens;
			}
		}
		
	protected:
		bool validateData(string* data) {
			try {
				if (data->status == "401") {
					throw "Couldn't get data, access token is invalid!";
				} else {
						throw "Something went wrong. Error: " + data->message;
				}
			} catch (string& str) {
				std::cout << str << std::endl;
				return false
			}
			return true
		}
		
		string* optimizeGrid(string* grid = new string[0]) {
			string* grid = this->sortGrid(grid);
			foreach ($grid as $id => $row) /////////////////////////////////////////// bla bla bla u get the drill
			{
				$grid[$id]['start_date'] = date('d/m/Y G:i', $row['start']);
				$grid[$id]['end_date'] = date('d/m/Y G:i', $row['end']);
				$grid[$id]['hour'] = round(($grid[$id]['start'] - strtotime(date('d-m-Y', $grid[$id]['start']) . ' 8:30')) / 3600);
				if ($grid[$id]['hour'] == 0) $grid[$id]['hour'] = 1; 
			}
			return grid;
		}
		
		string* sortGrid(string* grid = new string[0]) {
			int* timestamps = array(); ////////////////////////////////////// can't take it no more bye
			foreach ($grid as $key => $node)
			{
				if (in_array($node['start'], $timestamps))
				{
					unset($grid[$key]);
				} else {
					$timestamps[$key] = $node['start'];
				}
			}
			array_multisort($timestamps, SORT_ASC, $grid);
			return $grid;
		}
		
		string getBaseUrl(string uri = "") {
			return "https://" + this->school + ".zportal.nl/" + uri;
		}
		
		void saveToken(string& user, string& token) {
			
			if (file_exists('cache.json'))
			{
				current = json_decode(file_get_contents('cache.json'), true);
			}
			current->tokens->user = token;
			std::ofstream cache("cache.json", ios::out | ios::binary);
			if (cache) {
				cache << json_encode(current);
				cache.close();
			}
		}
		
	private:
		string callApi(string& uri, string* datafields) {
			string url = this->getBaseUrl(uri);
			string data = this->parseDataString(datafields);
			
			CURL* curl = curl_easy_init();
			curl_easy_setopt(curl, CURLOPT_URL, url + data);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, $this->secure);
			curl_easy_setopt(curl, CURLOPT_RETURNTRANSFER, true);
			CURLcode result = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			
			return result;
		}
		
		string callApiPost(string& uri) {
			string url = this->getBaseUrl(uri);
			data = rtrim(ltrim(this->parseDataString(datafields), "?"), "&");
			
			CURL* curl = curl_easy_init();
			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_POST, count(datafields));
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, this->secure);
			curl_easy_setopt(curl, CURLOPT_RETURNTRANSFER, true);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
			CURLcode result = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			
			return $result;
		}
		
		string parseDataString(string* datafields = new string[0]) {
				string str = "?";
				foreach ($datafields as $key => $value) { /////////////////////////////////////////// ok, soooo done
					$string .= $key . "=" . $value . "&";
				}
				return $string;
			}
}
