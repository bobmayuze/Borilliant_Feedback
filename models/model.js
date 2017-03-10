var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var demoSchema = new Schema({
    Name_g : String,
    Name_s : String,
    Difficulty: Number,
    Engagement: Number,
    Review: String,
    createTime: {
        type: Date,
        default: Date.now
    }
});

var CourseSchema = new Schema({
    Major : String,
    Name : String,
    Instuctor: String,
    Difficulty: Number,
    Boringness: Number,
    Time_Commitment: Number,
    Review: String,
    createTime: {
        type: Date,
        default: Date.now
    }
});

exports.Demo = mongoose.model('demo', demoSchema, 'demo');
exports.Course = mongoose.model('Course', CourseSchema)
