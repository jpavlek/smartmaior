from bottle import route, run, request, view, static_file, redirect, post
from flowthings import API, Token, mem
from settings import SETTINGS
#from alicebot import bot
from rivebot import bot

user = SETTINGS["user"]
master_token = SETTINGS["master_token"]
creds = Token(user, master_token)
api = API(creds, host="api.flowthings.io", secure=True)
app_path = "/%s/weather" % (user)
host = SETTINGS["host"]
port = SETTINGS["port"]

uids = {}

def base_path_created():
    resp = api.flow.find(mem.path == app_path)
    print str(resp)
    return len(resp) > 0

def create_application():
	if (base_path_created() == False):
		resp = api.flow.create({'path': app_path})
	return "Application ready to rock!"

def read_temperature(rs, args):
	# get the latest measure
	data = api.drop('f5754454a68056d7291ff72e7').find(limit=1)
	if len(data) == 0:
		return None
		
	singleDrop = data[0]
	elems = singleDrop.get('elems')
	temp = elems.get('temperature')
	value = temp.get('value')
	print "temperature", value
	return str(value)

@route('/')
@view('index')
def index():
	create_application()
	return {}

@post('/process')
def process():
	msg = request.forms.get("content")
	uid = request.forms.get("uid")
	if uid in uids:
		user = uids[uid]
	else:
		user = str(uid)
		uids[uid] = user
	responseMsg = bot.reply(user, msg)
	return dict(responseMsg=responseMsg)	

@route('/<filename:path>')
def send_static(filename):
	return static_file(filename, root='static/')
	
bot.set_subroutine("temperature", read_temperature)
run(host=host, port=port, debug=True)


