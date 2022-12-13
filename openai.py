import openai
openai.api_key = ""
completion = openai.Completion.create(
    engine="text-davinci-003", 
    prompt="", 
    max_tokens=1000
)
print(completion.choices[0].text)																																																																																																																																																																																																																																																														   