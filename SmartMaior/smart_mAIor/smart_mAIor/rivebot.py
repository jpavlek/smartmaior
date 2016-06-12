from rivescript import RiveScript

bot = RiveScript(utf8=True)
bot.load_directory("./replies")
bot.sort_replies()