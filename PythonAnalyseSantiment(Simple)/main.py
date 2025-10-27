from textblob import TextBlob

with open('myself.txt', 'r') as f:
    text = f.read()

blob = TextBlob(text)
sentiment = blob.sentiment

print(sentiment)
