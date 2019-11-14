param([String]$webHookUrl="", [String]$message)

#Create embed array
[System.Collections.ArrayList]$embedArray = @()

#Store embed values
$title       = 'Status'
$description =  $message
$color       = '1'

#Create thumbnail object
$thumbUrl = 'https://cdn.discordapp.com/emojis/634048265641263115.png?v=1' 
$thumbnailObject = [PSCustomObject]@{

    url = $thumbUrl

}

#Create embed object, also adding thumbnail
$embedObject = [PSCustomObject]@{

    title       = $title
    description = $description
    color       = $color
    thumbnail   = $thumbnailObject

}

#Add embed object to array
$embedArray.Add($embedObject) | Out-Null

#Create the payload
$payload = [PSCustomObject]@{

    embeds = $embedArray

}

#Send over payload, converting it to JSON
Invoke-RestMethod -Uri $webHookUrl -Body ($payload | ConvertTo-Json -Depth 4) -Method Post -ContentType 'application/json'